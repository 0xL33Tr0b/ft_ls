/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 20:47:29 by rdurst            #+#    #+#             */
/*   Updated: 2018/07/04 00:46:44 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	free_file - freeing a t_file *
*/

void	free_file(t_file *dir)
{
	if (dir != NULL)
	{
		ft_strdel(&dir->name);
		ft_strdel(&dir->perms);
		ft_strdel(&dir->user);
		ft_strdel(&dir->group);
		ft_strdel(&dir->size);
		ft_strdel(&dir->linkpath);
		free(dir);
	}
}

/*
**	free_dir - freeing a whole t_file **
*/

void	free_dir(t_file **dir, int size)
{
	int i;

	i = 0;
	if (dir != NULL)
	{
		ft_strdel(&dir[0]->path);
		while (i < size)
			free_file(dir[i++]);
		free(dir);
	}
}
