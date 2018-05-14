/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 13:16:35 by rdurst            #+#    #+#             */
/*   Updated: 2017/11/16 16:55:50 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char const *haystack, char const *needle)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = (char *)haystack;
	i = 0;
	if (ft_strlen(needle) == 0)
		return (tmp);
	while (tmp[i])
	{
		j = 0;
		while (tmp[i + j] == needle[j])
		{
			if (needle[j + 1] == '\0')
				return (&tmp[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
