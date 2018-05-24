/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 16:22:49 by rdurst            #+#    #+#             */
/*   Updated: 2018/05/17 17:53:23 by rdurst           ###   ########.fr       */
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

t_padding		*fill_padding(t_padding *padding, t_file **dir, int filesize)
{	
	int i;
	int links;
	int user;
	int group;
	int size;

	i = 0;
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

void			print_spaces(int nb)
{
	int i;

	i = -1;
	while (++i <= nb)
		ft_putchar(' ');
}
