/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 16:16:52 by rdurst            #+#    #+#             */
/*   Updated: 2017/11/14 18:15:01 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void const *s, int c, size_t n)
{
	unsigned char *str;

	str = (unsigned char *)s;
	c = (unsigned char)c;
	while (n)
	{
		if (*str == c)
			return (str);
		str++;
		n--;
	}
	return (NULL);
}
