/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 15:59:45 by msoulaim          #+#    #+#             */
/*   Updated: 2021/04/09 12:43:32 by msoulaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cwd(t_shell *shell)
{
	char	buf[4096 + 1];
	char	*cwd;
	char	*put;
	int		i;
	char	*tmp;

	tmp = NULL;
	cwd = getcwd(buf, 4096);
	(cwd == NULL) ?  cwd = ft_strdup("you removed your f directory") : 0;
	tmp = get_var_env("HOME", shell);
	if (tmp == NULL || ft_strlen(tmp) == 0)
		return (ft_strdup(cwd));
	i = 0;
	if (ft_strnequ(cwd, tmp, ft_strlen(tmp)) == 1)
	{
		put = replace_in_str(cwd, tmp, "~");
		free(tmp);
		return (put);
	}
	else
	{
		free(tmp);
		return (ft_strdup(cwd));
	}
}

void	ft_put4str(char *a, char *b, char *c, char *d)
{
	ft_putstr_fd(a, 2);
	ft_putstr_fd(b, 2);
	ft_putstr_fd(c, 2);
	ft_putstr_fd(d, 2);
}

char	**d_realloc(char **str, int new_size)
{
	char	**new;
	int		i;

	new = (char **)ft_memalloc(sizeof(char *) * (new_size + 1));
	i = -1;
	while (str[++i] && i < new_size)
	{
		new[i] = ft_strdup(str[i]);
		free(str[i]);
	}
	new[new_size] = NULL;
	free(str);
	return (new);
}

char	*join_three(char *str1, char *str2, char *str3)
{
	char *s;
	char *ret;

	s = ft_strjoin(str1, str2);
	ret = ft_strjoin(s, str3);
	(s) ? free(s) : 0;
	return (ret);
}

int		str2len(char **str)
{
	if (*str)
		return (str2len(str + 1) + 1);
	return (0);
}
