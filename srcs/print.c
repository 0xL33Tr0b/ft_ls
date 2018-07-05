/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 13:19:34 by rdurst            #+#    #+#             */
/*   Updated: 2018/07/05 01:48:02 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	print_l - prints one line/file from t_file * (-l)
*/

void	print_l(t_file *dir, t_info info, t_pad *pad)
{
	if (dir->error == EACCES && info.type == 1)
		perm_denied(dir->name, info);
	else if (dir->error == EPERM)
		return ;
	else
	{
		ft_putstr(dir->perms);
		print_spaces(pad->links - ft_nbrlen(dir->links) + 1);
		ft_putnbr(dir->links);
		print_spaces(pad->user - ft_strlen(dir->user));
		ft_putstr(dir->user);
		print_spaces(pad->group - ft_strlen(dir->group) + 1);
		ft_putstr(dir->group);
		print_spaces(pad->size - ft_strlen(dir->size) + 1);
		ft_putstr(dir->size);
		print_spaces(0);
		print_timestamp(dir->timestamp);
		print_spaces(0);
		ft_putstr(dir->name);
		if (dir->linkpath != NULL)
			print_link(dir->linkpath);
		ft_putchar('\n');
	}
}

/*
**	two_points - prints "file:"
*/

void	two_points(char *file)
{
	ft_putstr(file);
	ft_putstr(":\n");
}

/*
**	print_timestamp - printing timestamp from a file
**	in case of -l
*/

void	print_timestamp(long timestamp)
{
	char *ret;

	if ((ret = ctime(&timestamp)) == NULL)
		return ;
	ret[16] = '\0';
	ft_putstr(ret + 4);
}

/*
**	print_spaces - prints 'nb' spaces
*/

void	print_spaces(int nb)
{
	int i;

	i = -1;
	while (++i <= nb)
		ft_putchar(' ');
}

/*
**	print_link - prints '-> linkpath'
*/

void	print_link(char *linkpath)
{
	ft_putstr(" -> ");
	ft_putstr(linkpath);
}
