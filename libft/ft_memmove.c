/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 16:03:31 by rdurst            #+#    #+#             */
/*   Updated: 2017/11/16 21:51:02 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*s1;
	char	*s2;

	s1 = (char*)dest;
	s2 = (char*)src;
	if (s2 < s1)
	{
		while (n--)
			s1[n] = s2[n];
	}
	else
		ft_memcpy(s1, s2, n);
	return (s1);
}
