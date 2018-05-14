/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 01:38:04 by rdurst            #+#    #+#             */
/*   Updated: 2017/11/20 17:50:43 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		size;
	char	*fresh;
	int		i;
	int		k;

	if (!s)
		return (NULL);
	size = ft_trimsize(s);
	i = 0;
	k = 0;
	if ((fresh = (char *)malloc(sizeof(char) * size + 1)) == NULL)
		return (NULL);
	while (ft_isblanked(s[i]) == 1)
		i++;
	while (k < size)
		fresh[k++] = s[i++];
	fresh[k] = '\0';
	return (fresh);
}
