/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcolor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 22:53:50 by rdurst            #+#    #+#             */
/*   Updated: 2018/06/11 15:03:00 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putcolor(char *color, char *str)
{
	ft_putstr(color);
	ft_putstr(str);
	ft_putstr(RESET);
	ft_putchar('\n');
}
