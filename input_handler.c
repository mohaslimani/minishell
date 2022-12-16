/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 18:26:54 by msoulaim          #+#    #+#             */
/*   Updated: 2021/04/03 17:24:45 by msoulaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*skip_all(char *str, char c1, char c2)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c1 || str[i] == c2)
			str[i] = ' ';
		i++;
	}
	return (str);
}

char		*skip_all_dollars(char *str)
{
	int		i;
	char	*out;

	i = 0;
	out = NULL;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\0' && str[i + 1] != ' ')
			i = posend_var(&str[i + 1]) + i;
		else
			out = joinc(&out, str[i]);
		i++;
	}
	return (out);
}

char		*handle_home(char *str, t_shell *shell)
{
	int		i;
	char	*tmp;
	char	*out;
	char	*home;

	out = ft_strnew(1);
	home = get_var_env("HOME", shell);
	i = 0;
	(str[0] == '~' && (str[1] == ' ' || str[1] == '\0')) ?
	(out = ft_strjoin("", home))
	: (out = joinc(&out, str[0]));
	while (str[++i])
	{
		if ((str[i] == '~' && str[i - 1] == ' ') \
		&& (str[i + 1] == ' ' || str[i + 1] == '\0' || str[i + 1] == '/'))
		{
			tmp = out;
			out = ft_strjoin(out, home);
			free(tmp);
		}
		else
			out = joinc(&out, str[i]);
	}
	(home) ? (free(home)) : 0;
	return (out);
}

char		*handle_var(char *str, t_shell *shell)
{
	char	*out;
	char	*tmp;
	int		i;

	i = 0;
	out = NULL;
	tmp = NULL;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\0')
		{
			tmp = var_cr(&str[i + 1], shell);
			if (tmp != NULL)
			{
				i = posend_var(&str[i + 1]) + i;
				out = joinf(&out, &tmp);
			}
			else
				out = joinc(&out, str[i]);
		}
		else
			out = joinc(&out, str[i]);
		i++;
	}
	return (out);
}

void		handle_dollar(char **input, t_shell *shell)
{
	char	*tmp;
	char	*tmp2;
	char	*ret;

	tmp = *input;
	while ((ret = ft_strstr(*input, "$?")))
	{
		tmp2 = ft_itoa(shell->last_ret);
		*input = replace_in_str(*input, "$?", tmp2);
		(tmp) ? free(tmp) : 0;
		(tmp2) ? free(tmp2) : 0;
		tmp = *input;
		if ((ret = ft_strstr(*input, "$?")) && ret[2])
			break ;
	}
	*input = handle_var(*input, shell);
	free(tmp);
}
