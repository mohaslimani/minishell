/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 15:23:50 by msoulaim          #+#    #+#             */
/*   Updated: 2022/12/16 13:31:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_env(char *var, t_shell *shell)
{
	int		i;
	char	**g_env;
	char	*tmp;

	i = 0;
	g_env = shell->env;
	tmp = ft_strjoin(var, "=");
	while (g_env[i])
	{
		if (ft_strncmp(tmp, g_env[i], ft_strlen(tmp)) == 0)
		{
			free(tmp);
			return (ft_strdup(g_env[i]));
		}
		i++;
	}
	free(tmp);
	return (NULL);
}

void	print_env(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->env[i] != NULL)
	{
		ft_putendl(shell->env[i]);
		i++;
	}
}

char	*get_var_env(char *var, t_shell *shell)
{
	char *tmp;
	char *ret;

	tmp = search_env(var, shell);
	ret = NULL;
	if (tmp)
	{
		ret = ft_strdup(ft_strchr(tmp, '=') + 1);
		free(tmp);
	}
	return (ret);
}

void	env_dup(char **env, t_shell *shell)
{
	int		i;
	char	**g_env;

	i = 0;
	g_env = (char **)malloc(sizeof(char *) * (str2len(env) + 1));
	if (g_env == NULL)
	{
		ft_putendl_fd("malloc failed at env_dup", 2);
		exit(EXIT_FAILURE);
	}
	while (env[i])
	{
		g_env[i] = ft_strdup(env[i]);
		if (g_env[i] == NULL)
		{
			free_until(g_env, i);
			free(g_env);
			ft_putendl_fd("malloc failed at env_dup", 2);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	g_env[i] = NULL;
	shell->env = g_env;
	shell->last_ret = 0;
}
