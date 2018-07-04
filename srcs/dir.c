/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 20:28:10 by rdurst            #+#    #+#             */
/*   Updated: 2018/07/04 03:06:21 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	init_dir - mallocing a t_file **
*/

t_file	**init_dir(t_file **dir, int size)
{
	int i;

	i = 0;
	if ((dir = (t_file **)malloc(sizeof(t_file*) * size)) == NULL)
		return (NULL);
	while (i < size)
	{
		if ((dir[i] = malloc(sizeof(t_file))) == NULL)
			return (NULL);
		dir[i]->path = NULL;
		dir[i]->name = NULL;
		dir[i]->perms = NULL;
		dir[i]->links = 0;
		dir[i]->linkpath = NULL;
		dir[i]->user = NULL;
		dir[i]->group = NULL;
		dir[i]->size = 0;
		dir[i]->timestamp = 0;
		dir[i]->ntimestamp = 0;
		dir[i]->blocks = 0;
		i++;
	}
	if (i == size)
		return (dir);
	return (NULL);
}

/*
**	fill_stats - filling a t_file * with the struct stat
**		and the stats.c functions
*/

t_file	*fill_stats(t_file *dir, char *name, char *path, t_stats *stats)
{
	dir->name = ft_strdup(name);
	dir->path = path;
	dir->perms = find_modes(stats);
	dir->links = stats->st_nlink;
	dir->linkpath = find_link(path, dir->name);
	dir->user = find_user(stats);
	dir->group = find_group(stats);
	dir->size = stats->st_size;
	dir->timestamp = stats->st_mtime;
	dir->ntimestamp = stats->st_mtimespec.tv_nsec;
	dir->blocks = stats->st_blocks;
	dir->error = find_error(name);
	free(stats);
	return (dir);
}

/*
**	fill_dir - filling a t_file ** with stats
**		for each file of the dir from ls
*/

t_file	**fill_dir(t_file **dir, t_info info, char *path)
{
	int				i;
	struct dirent	*file;
	struct stat		*stats;
	DIR				*dirpointer;
	char			*tmp;

	i = 0;
	if ((dirpointer = opendir(path)) == NULL)
		return (dir);
	dir[0]->path = ft_strdup(path);
	while (i < info.size && (file = readdir(dirpointer)) != NULL)
	{
		tmp = ft_strjoin(path, file->d_name);
		if ((stats = (struct stat *)malloc(sizeof(struct stat))) != NULL)
		{
			lstat(tmp, stats);
			dir[i] = fill_stats(dir[i], file->d_name, dir[0]->path, stats);
		}
		ft_strdel(&tmp);
		i++;
	}
	(void)closedir(dirpointer);
	return (dir);
}

/*
**	sfiles - filling a t_file ** with the files
**		from single_file_ls
*/

t_file	**sfiles(char **av, t_info info, t_file **dir)
{
	int			i;
	int			j;
	struct stat	*stats;

	i = 0;
	j = 0;
	stats = NULL;
	dir[0]->path = ft_strdup("");
	while (j < info.size)
	{
		if (valid_arg(av[i]) == 1)
		{
			if ((stats = (struct stat *)malloc(sizeof(struct stat))) == NULL)
				return (dir);
			lstat(av[i], stats);
			dir[j] = fill_stats(dir[j], av[i], dir[0]->path, stats);
			j++;
		}
		i++;
	}
	return (dir);
}
