/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 16:22:49 by rdurst            #+#    #+#             */
/*   Updated: 2018/07/02 11:15:56 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
	init_pad - mallocing a t_pad *
*/

t_pad		*init_pad(void)
{
	t_pad *padding;

	padding = malloc(sizeof(t_pad));
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

/*
	fill_padding - fills t_pad * with max width of each
	field of a t_file **
*/

t_pad		*fill_padding(t_pad *padding, t_file **dir, int filesize)
{	
	int i;
	int links;
	int user;
	int group;
	int size;

	i = 0;
	if (dir == NULL)
		return (NULL);
	while (i < filesize)
	{
		links = ft_nbrlen(dir[i]->links);
		user = ft_strlen(dir[i]->user);
		group = ft_strlen(dir[i]->group);
		size = ft_nbrlen(dir[i]->size);
		if (links > padding->links)
			padding->links = links;
		if (user > padding->user)
			padding->user = user;
		if (group > padding->group)
			padding->group = group;
		if (size > padding->size)
			padding->size = size;
		i++;
	}
	return (padding);
}

/*
	print_spaces - prints 'nb' spaces
*/

void			print_spaces(int nb)
{
	int i;

	i = -1;
	while (++i <= nb)
		ft_putchar(' ');
}
