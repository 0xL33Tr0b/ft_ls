#include "ft_ls.h"

/*
	ft_dirlen - returns the number of files
		in the specified directory
*/

int	ft_dirlen(char *name, char *path)
{
	int		ret;
	DIR		*dir;
	struct dirent	*files;
	char		*tmp;

	ret = 0;
	tmp = ft_strdup(path);
	path = ft_strjoin(tmp, name);
	ft_strdel(&tmp);
	if ((dir = opendir(path)) == NULL)
		return (1);
	else
		while ((files = readdir(dir)) != NULL)
			ret++;
	(void)closedir(dir);
	return (ret);
}

/*
	print_blocks - prints the 'total 0' in -l
		with the total number of blocks in a directory
*/

void	print_blocks(t_file **dir, int size, t_options *options)
{
	int ret;
	int i;

	i = 0;
	ret = 0;
	while (i < size)
	{
		if (!(options->a == 0 && dir[i]->name[0] == '.'))
			ret += dir[i]->blocks;
		i++;
	}
	ft_putstr("total ");
	ft_intendl(ret);
}

/*
	get_timestamp - returns the last modification
		timestamp from a valid file or 0
*/

long	get_timestamp(char *dir)
{
	struct stat	*stats;

	stats = malloc(sizeof(struct stat));
	if (lstat(dir, stats) == -1)
		return (0);
	return (stats->st_mtime);
}

/*
	next_dir_offset - returns the number of files
		before the next dir in **av or 0
		if there is no remaining ones
*/

int	next_dir_offset(char **av)
{
	int ret;

	ret = 1;
	while (av[ret] && valid_arg(av[ret]) != 2)
		ret++;
	if (valid_arg(av[ret]) == 2)
		return (ret);
	else
		return (0);
}

/*
	valid_path - adds a '/' to a path
		if there is no one
*/

char	*valid_path(char *path)
{
	int 	i;
	char	*tmp;

	i = 0;
	if (!path)
		return (NULL);
	while (path[i])
		i++;
	if (i == 1 || path[i] == '/')
		return (path);
	else
	{
		tmp = ft_strdup(path);
		path = ft_strjoin(tmp, "/");
		ft_strdel(&tmp);
		return (path);
	}
}
