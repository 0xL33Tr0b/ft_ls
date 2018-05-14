/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 21:05:30 by rdurst            #+#    #+#             */
/*   Updated: 2018/01/12 15:53:19 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*fresh;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	fresh = (char *)malloc(sizeof(char) * len + 1);
	if (fresh == NULL)
		return (NULL);
	while (s[start] && i < len)
		fresh[i++] = s[start++];
	fresh[i] = '\0';
	return (fresh);
}
