/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:59:39 by rdurst            #+#    #+#             */
/*   Updated: 2017/11/14 18:17:51 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char const *str, int c)
{
	int len;

	len = ft_strlen(str);
	while (len && str[len] != (char)c)
		len--;
	if (str[len] == (char)c)
		return ((char *)&str[len]);
	return (NULL);
}
