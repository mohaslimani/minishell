/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 15:03:43 by msoulaim          #+#    #+#             */
/*   Updated: 2021/01/16 16:37:23 by msoulaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_until(char **str, int n)
{
	int i;

	i = 0;
	while (str[i] && i < n)
		ft_strdel(&str[i++]);
}

int		free2dim(char ***pointer)
{
	if (pointer && *pointer && **pointer)
	{
		free_until(*pointer, INT_MAX);
		free(*pointer);
	}
	return (1);
}
