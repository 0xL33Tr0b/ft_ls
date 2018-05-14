/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:44:00 by rdurst            #+#    #+#             */
/*   Updated: 2017/11/16 17:45:35 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char const *src, size_t size)
{
	size_t len;

	len = ft_strlen(dst);
	if (size <= len)
		return (size + ft_strlen(src));
	ft_strncat(dst, src, size - len - 1);
	return (len + ft_strlen(src));
}
