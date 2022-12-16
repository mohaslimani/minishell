/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 15:26:22 by msoulaim          #+#    #+#             */
/*   Updated: 2021/01/17 12:51:20 by msoulaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_flag(char *arg, int n)
{
	int	i;

	i = 1;
	if (arg[0] != '-')
		return (0);
	while (arg[i])
	{
		if (arg[i] != n)
			return (0);
		i++;
	}
	return (1);
}

int		ft_echo(char **args)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (args[i] && ft_strequ(args[i], "-n") &&\
	check_flag(args[i], 'n') && (n = 1))
		i++;
	while (args[i])
	{
		ft_putstr(args[i]);
		if (args[++i])
			write(1, " ", 1);
	}
	if (n == 0)
		write(1, "\n", 1);
	return (0);
}

int		my_chdir(char *path, int print, t_shell *shell)
{
	struct stat	f;
	char		*parsed_home;
	char		buff[4096];

	set_env("OLDPWD", getcwd(buff, 4095), shell);
	if (!chdir(path))
	{
		parsed_home = handle_home(path, shell);
		if (print == 1)
			ft_putendl(parsed_home);
		free(parsed_home);
		set_env("PWD", getcwd(buff, 4095), shell);
		return (0);
	}
	if (stat(path, &f) == -1 || access(path, F_OK) == -1)
		ft_putstr_fd("cd: no such file or directory: ", 2);
	else if (!(f.st_mode & S_IFDIR))
		ft_putstr_fd("cd: not a directory: ", 2);
	else if (!(f.st_mode & S_IREAD) || access(path, R_OK) == -1)
		ft_putstr_fd("cd: permission denied: ", 2);
	ft_putendl(path);
	return (1);
}

int		cd_replace(char **args, t_shell *shell)
{
	char	*cwd;
	char	buff[4096 + 1];
	char	*tmp;
	int		ret;

	cwd = getcwd(buff, 4096);
	if (!(tmp = replace_in_str(cwd, args[0], args[1])))
	{
		ft_putstr("cd: string not in pwd: ");
		ft_putendl(args[0]);
		free(tmp);
		return (1);
	}
	ret = my_chdir(tmp, 1, shell);
	free(tmp);
	return (ret);
}

int		ft_cd(char **args, t_shell *shell)
{
	char	*home;
	int		ret;

	if (str2len(args) > 2)
		ft_putendl_fd("cd: too many arguments", 2);
	else if (str2len(args) == 0 || (ft_strequ(args[0], "--")\
	&& str2len(args) == 1))
	{
		home = get_var_env("HOME", shell);
		ret = my_chdir(home, 0, shell);
		free(home);
		return (ret);
	}
	else if (ft_strequ(args[0], "-") && str2len(args) == 1)
	{
		home = get_var_env("OLDPWD", shell);
		(home) ? (ret = my_chdir(home, 1, shell)) : 0;
		(!home) ? (ft_putendl_fd("cd: OLDPWD not set", 2)) : free(home);
		return ((home) ? (ret) : (1));
	}
	else if (str2len(args) == 2)
		return (cd_replace(args, shell));
	ret = my_chdir(args[0], 0, shell);
	return (ret);
}
