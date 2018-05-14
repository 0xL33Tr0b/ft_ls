/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 22:06:08 by rdurst            #+#    #+#             */
/*   Updated: 2017/11/14 18:28:22 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*result;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	result = (char *)malloc(sizeof(char) * ft_intsize(n) + 1);
	i = ft_intsize(n);
	if (result == NULL)
		return (NULL);
	result[i--] = '\0';
	if (n < 0)
	{
		result[0] = '-';
		n = -n;
	}
	if (n == 0)
		result[0] = '0';
	while (n != 0)
	{
		result[i--] = (n % 10) + '0';
		n /= 10;
	}
	return (result);
}
