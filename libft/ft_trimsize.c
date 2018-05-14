/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trimsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 01:23:44 by rdurst            #+#    #+#             */
/*   Updated: 2017/11/20 17:49:54 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_trimsize(char const *str)
{
	int result;
	int i;

	result = 0;
	i = 0;
	while (str[i] && ft_isblanked(str[i]) == 1)
	{
		result++;
		i++;
	}
	if (result == (int)ft_strlen(str))
		return (0);
	i = ft_strlen(str) - 1;
	while (i >= 0 && ft_isblanked(str[i]) == 1)
	{
		result++;
		i--;
	}
	return (ft_strlen(str) - result);
}
