/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 15:50:47 by msoulaim          #+#    #+#             */
/*   Updated: 2021/01/17 14:12:27 by msoulaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			search_env_pos(char *var, t_shell *shell)
{
	int		i;
	int		j;
	char	**g_env;
	char	*tmp;

	i = 0;
	g_env = shell->env;
	tmp = ft_strjoin(var, "=");
	while (g_env[i])
	{
		j = 0;
		if (ft_strncmp(tmp, g_env[i], ft_strlen(tmp)) == 0)
		{
			free(tmp);
			return (i);
		}
		i++;
	}
	free(tmp);
	return (-1);
}

void		remove_env_var(int var_pos, t_shell *shell)
{
	int		i;
	int		var_count;

	free(shell->env[var_pos]);
	shell->env[var_pos] = NULL;
	i = var_pos;
	var_count = var_pos + 1;
	while (shell->env[i + 1])
	{
		shell->env[i] = ft_strdup(shell->env[i + 1]);
		free(shell->env[i + 1]);
		i++;
		var_count++;
	}
	shell->env = d_realloc(shell->env, var_count - 1);
}

void		set_env(char *arg1, char *arg2, t_shell *shell)
{
	int		pos;

	if ((pos = search_env_pos(arg1, shell)) != -1)
	{
		free(shell->env[pos]);
		shell->env[pos] = join_three(arg1, "=", arg2);
	}
	else
	{
		shell->env = d_realloc(shell->env, str2len(shell->env) + 1);
		shell->env[str2len(shell->env)] = join_three(arg1, "=", arg2);
	}
}

int			ft_setenv(char **args_cmd, t_shell *shell)
{
	int		i;

	i = str2len(args_cmd);
	if (i > 2)
	{
		ft_putendl_fd("setenv: Too many arguments.", 2);
		return (1);
	}
	else if (i == 1)
		set_env(args_cmd[0], "", shell);
	else if (i == 2)
		set_env(args_cmd[0], args_cmd[1], shell);
	return (0);
}

int			ft_unsetenv(char **args, t_shell *shell)
{
	int		i;
	int		pos;

	i = 0;
	if (str2len(args) == 0)
	{
		ft_putendl_fd("unsetenv: Too few arguments.", 2);
		return (1);
	}
	while (args[i])
	{
		if ((pos = search_env_pos(args[i], shell)) != -1)
			remove_env_var(pos, shell);
		i++;
	}
	return (0);
}
