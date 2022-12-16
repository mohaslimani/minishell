/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 14:53:02 by msoulaim          #+#    #+#             */
/*   Updated: 2021/04/03 15:07:58 by msoulaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*check_path(char *command, t_shell *shell)
{
	struct stat	f;
	char		*path;
	char		**paths;
	int			i;

	i = -1;
	path = get_var_env("PATH", shell);
	paths = ft_strsplit(path, ':');
	(path) ? (free(path)) : 0;
	if (lstat(command, &f) != -1 && (f.st_mode & S_IFREG) && (free2dim(&paths)))
		return (ft_strdup(command));
	while (paths && paths[++i])
	{
		path = join_three(paths[i], "/", command);
		if (lstat(path, &f) != -1 && (f.st_mode & S_IFREG)\
			&& free2dim(&paths))
			return (path);
		(path) ? free(path) : 0;
	}
	free2dim(&paths);
	return (NULL);
}

int			if_exe(char *command, char *cmd)
{
	struct stat f;

	if (lstat(command, &f) != -1 && (f.st_mode & S_IFREG)\
	&& !(f.st_mode & S_IXUSR))
	{
		ft_put4str("minishell: permession denied: ", cmd, "\n", "");
		return (0);
	}
	return (1);
}

int			run_command(char *path, char **args, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		execve(path, args, shell->env);
	else if (pid < 0)
	{
		ft_putendl("Fork failed to create a new process.");
		return (-1);
	}
	wait(&pid);
	(WIFEXITED(pid)) ? (shell->last_ret = WEXITSTATUS(pid)) : 0;
	(WIFSIGNALED(pid)) ? (shell->last_ret = WTERMSIG(pid)) : 0;
	(WIFSTOPPED(pid)) ? (shell->last_ret = WSTOPSIG(pid)) : 0;
	return (1);
}

int			builtins(char **args_cmd, t_shell *shell)
{
	if (ft_strequ(args_cmd[0], "echo"))
		return (ft_echo(args_cmd + 1));
	else if (ft_strequ(args_cmd[0], "cd"))
		return (ft_cd(args_cmd + 1, shell));
	else if (ft_strequ(args_cmd[0], "setenv"))
		return (ft_setenv(args_cmd + 1, shell));
	else if (ft_strequ(args_cmd[0], "unsetenv"))
		return (ft_unsetenv(args_cmd + 1, shell));
	else if (ft_strequ(args_cmd[0], "env"))
	{
		print_env(shell);
		return (1);
	}
	return (-1);
}

void		exe(char *in, t_shell *shell)
{
	char	**args_cmd;
	char	*path;

	args_cmd = ft_strsplit(in, ' ');
	path = NULL;
	if (args_cmd != NULL && args_cmd[0] &&\
	(shell->last_ret = builtins(args_cmd, shell)) == -1)
	{
		path = check_path(args_cmd[0], shell);
		if (path == NULL)
			ft_put4str("minishell: command not found: ", args_cmd[0], "\n", "");
		else if (if_exe(path, args_cmd[0]))
			run_command(path, args_cmd, shell);
		(path) ? (free(path)) : 0;
	}
	if (args_cmd)
	{
		free_until(args_cmd, INT_MAX);
		free(args_cmd);
		args_cmd = NULL;
	}
}
