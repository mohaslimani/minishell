/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 14:37:01 by msoulaim          #+#    #+#             */
/*   Updated: 2021/01/12 16:06:18 by msoulaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nbrstr(char const *str, char c)
{
	int i;
	int nb;

	i = 0;
	nb = 0;
	while (str && str[i])
	{
		if ((str[i] != c) && (str[i + 1] == c))
			nb++;
		i++;
	}
	if (str[i - 1] != c && str[i] == '\0')
		nb++;
	return (nb);
}
