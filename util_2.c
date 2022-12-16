/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:16:51 by msoulaim          #+#    #+#             */
/*   Updated: 2021/01/16 16:39:12 by msoulaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_in_str(char *haystack, char *needle, char *str)
{
	char *tmp;
	char *tmp2;
	char *p1;
	char *ret;

	tmp = ft_strstr(haystack, needle);
	if (!tmp)
		return (NULL);
	p1 = ft_strsub(haystack, 0, ft_strlen(haystack) - ft_strlen(tmp));
	tmp2 = ft_strjoin(p1, str);
	ret = ft_strjoin(tmp2, &tmp[ft_strlen(needle)]);
	free(p1);
	free(tmp2);
	return (ret);
}

int		posend_var(char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z')\
	|| (str[i] >= 'A' && str[i] <= 'Z') || (str[i] == '_'))
		i++;
	return (i);
}

char	*joinf(char **str1, char **str2)
{
	char *ret;

	if (*str1)
		ret = ft_strjoin(*str1, *str2);
	else
		ret = ft_strjoin("", *str2);
	if (*str1 != NULL)
		free(*str1);
	if (*str2 != NULL)
		free(*str2);
	return (ret);
}

char	*joinc(char **str, char c)
{
	char cc[2];
	char *tmp;

	cc[0] = c;
	cc[1] = '\0';
	if (!str || !*str)
		return (ft_strdup(cc));
	tmp = *str;
	*str = ft_strjoin(*str, cc);
	free(tmp);
	return (*str);
}

char	*var_cr(char *str, t_shell *shell)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strsub(str, 0, posend_var(str));
	tmp2 = get_var_env(tmp, shell);
	ft_strdel(&tmp);
	if (tmp2 != NULL)
		return (tmp2);
	else
		return (NULL);
}
