/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strucpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 13:59:46 by rdurst            #+#    #+#             */
/*   Updated: 2018/03/16 12:40:56 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strucpy(char **dest, char *tocpy, char c)
{
	int i;

	i = 0;
	while (tocpy[i])
	{
		if (tocpy[i] == c || tocpy[i] == '\0')
			break ;
		i++;
	}
	if (!(*dest = ft_strnew(i + 1)))
		return (-1);
	ft_strncpy(*dest, tocpy, i);
	return (i);
}
