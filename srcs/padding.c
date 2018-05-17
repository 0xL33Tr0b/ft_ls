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

t_padding		*fill_padding(t_padding *padding, char *filename, char *path)
{	
	struct group	*grp;
	struct passwd	*usr;
	struct stat		*buf;
	int				links;
	int				user;
	int				group;
	int				size;
	int				ret;

	buf = malloc(sizeof(struct stat));
	ret = 0;
	if ((ret = stat(ft_strjoin(valid_path(path), filename), buf)) == -1)
		return (padding);
	links = ft_nbrlen(buf->st_nlink);
	usr = getpwuid(buf->st_uid);
	user = ft_strlen(usr->pw_name);
	grp = getgrgid(buf->st_gid);
	group = ft_strlen(grp->gr_name);
	size = ft_nbrlen(buf->st_size);
	if (links > padding->links)
		padding->links = links;
	if (user > padding->user)
		padding->user = user;
	if (group > padding->group)
		padding->group = group;
	if (size > padding->size)
		padding->size = size;
	return (padding);
}
