#include "ft_ls.h"

void	free_file(t_file *dir)
{
	ft_strdel(&dir->name);
	ft_strdel(&dir->perms);
	ft_strdel(&dir->user);
	ft_strdel(&dir->group);
	ft_strdel(&dir->linkpath);
	free(dir);
}

void	free_dir(t_file **dir, int size)
{
	int i;

	i = 0;
	ft_strdel(&dir[0]->path);
	while (i < size)
		free_file(dir[i++]);
}

t_file	**init_dir(t_file **dir, int size)
{
	int i;

	i = 0;
	if((dir = (t_file **)malloc(sizeof(t_file*) * size)) == NULL)
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

t_file	**fill_dir(t_file **dir, int size, char *path, t_options *options)
{
	int		i;
	struct dirent	*file;
	struct stat	*stats;
	DIR		*dirpointer;
	char		*tmp;

	i = 0;
	if ((dirpointer = opendir(path)) == NULL)
		return (NULL);
	dir[0]->path = ft_strdup(path);
	while (i < size)
	{
		if ((file = readdir(dirpointer)) == NULL)
			return (NULL);
		tmp = ft_strjoin(path, file->d_name);
		if ((stats = (struct stat *)malloc(sizeof(struct stat))) == NULL)
			return (NULL);
		if ((lstat(tmp, stats)) == -1)
		{
			if (options->l)
				not_permitted(file->d_name);
			dir[i]->name = ft_strdup(file->d_name);
			dir[i]->size = -1;
		}
		else
		{
			dir[i]->name = ft_strdup(file->d_name);
			dir[i]->path = dir[0]->path;
			dir[i]->perms = find_modes(stats);
			dir[i]->links = stats->st_nlink;
			dir[i]->linkpath = find_link(dir[0]->path, dir[i]->name);
			dir[i]->user = find_user(stats);
			dir[i]->group = find_group(stats);
			dir[i]->size = stats->st_size;
			dir[i]->timestamp = stats->st_mtime;
			dir[i]->ntimestamp = stats->st_mtimespec.tv_nsec;
			dir[i]->blocks = stats->st_blocks;
			ft_strdel(&tmp);
		}
		free(stats);
		i++;
	}
	(void)closedir(dirpointer);
	return (dir);
}

t_file	**fill_files(char **av, int begin, int size, t_file **dir)
{
	int i;
	int j;
	struct stat *stats;

	i = begin;
	j = 0;
	stats = NULL;
	while (j < size)
	{
		if (valid_arg(av[i]) == 1)
		{
			if ((stats = (struct stat *)malloc(sizeof(struct stat))) == NULL)
				return (NULL);
			if ((lstat(av[i], stats)) == -1)
				return (NULL);
			dir[j]->name = ft_strdup(av[i]);
			dir[j]->perms = find_modes(stats);
			dir[j]->links = stats->st_nlink;
			dir[j]->user = find_user(stats);
			dir[j]->group = find_group(stats);
			dir[j]->size = stats->st_size;
			dir[j]->timestamp = stats->st_mtime;
			dir[j]->ntimestamp = stats->st_mtimespec.tv_nsec;
			dir[j]->blocks = stats->st_blocks;
			j++;
			free(stats);
		}
		i++;
	}
	return (dir);
}
