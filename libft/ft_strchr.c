/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:53:44 by rdurst            #+#    #+#             */
/*   Updated: 2018/03/18 16:34:38 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char const *str, int c)
{
	char *tmp;

	tmp = (char *)str;
	while (*tmp)
	{
		if (*tmp == c)
			return (tmp);
		tmp++;
	}
	if (*tmp == c)
		return (tmp);
	return (NULL);
}
