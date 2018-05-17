/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 16:22:49 by rdurst            #+#    #+#             */
/*   Updated: 2018/05/17 17:14:29 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_padding		*init_padding(void)
{
	t_padding *padding;

	padding = malloc(sizeof(t_padding));
	padding->directory_number = 0;
	padding->perms = 0;
	padding->links = 0;
	padding->user = 0;
	padding->group = 0;
	padding->size = 0;
	padding->timestamp = 0;
	padding->name = 0;
	return (padding);
}

t_padding		*fill_padding(t_padding *padding, char *name)
{	
	
	return (padding);
}
