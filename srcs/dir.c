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

t_file	*fill_stats(t_file *dir, char *name, char *path, struct stat *stats, t_options *options)
{	
	if (options->l && dir->error == EPERM)
		not_permitted(name);
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
	return (dir);

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
		lstat(tmp, stats);
		dir[i]->error = find_error(file->d_name);
		dir[i] = fill_stats(dir[i], file->d_name, dir[0]->path, stats, options);
		free(stats);
		ft_strdel(&tmp);
		i++;
	}
	(void)closedir(dirpointer);
	return (dir);
}

t_file	**fill_files(char **av, int begin, int size, t_file **dir, t_options *options)
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
			lstat(av[i], stats);
			dir[j]->error = find_error(av[i]);
			if (dir[j]->error == EACCES)
			{
				perm_denied(av[i]);
				dir[j]->error = 1337;
			}
			dir[j] = fill_stats(dir[j], av[i], "", stats, options);
			j++;
			free(stats);
		}
		i++;
	}
	return (dir);
}
