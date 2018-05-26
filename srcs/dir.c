#include "ft_ls.h"

int	ft_dirlen(char *name, char *path)
{
	int		ret;
	DIR		*dir;
	struct dirent	*files;

	ret = 0;	
	if ((dir = opendir(ft_strjoin(path, name))) == NULL)
		return (1);
	else
		while ((files = readdir(dir)) != NULL)
			ret++;
	(void)closedir(dir);
	return (ret);
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
		dir[i]->name = NULL;
		dir[i]->perms = NULL;
		dir[i]->links = 0;
		dir[i]->user = NULL;
		dir[i]->group = NULL;
		dir[i]->size = 0;
		dir[i]->timestamp = NULL;
		dir[i]->blocks = 0;
		i++;
	}
	return (dir);
}

char	*find_user(struct stat *stats)
{
	struct passwd	*usr;

	if ((usr = getpwuid(stats->st_uid)) == NULL)
		return (NULL);
	return (usr->pw_name);
}

char	*find_group(struct stat *stats)
{
	struct group	*grp;

	if ((grp = getgrgid(stats->st_gid)) == NULL) 
		return (NULL);
	return (grp->gr_name);
}

char	*find_timestamp(struct stat *stats)
{
	char *ret;
	if ((ret = (char *)malloc(sizeof(char) * 24)) == NULL)
		return (NULL);
	if ((ret = ctime_r(&stats->st_mtime, ret)) == NULL)
		return (NULL);
	ret[16] = '\0';
	return (ret);
}

t_file	**fill_dir(t_file **dir, int size, char *path)
{
	int		i;
	struct dirent	*file;
	struct stat	*stats;
	DIR		*dirpointer;

	i = 0;
	if ((dirpointer = opendir(path)) == NULL)
		return (NULL);
	while (i < size)
	{
		stats = (struct stat *)malloc(sizeof(struct stat));
		if ((file = readdir(dirpointer)) == NULL)
			return (NULL);
		if ((stat(ft_strjoin(path, file->d_name), stats)) == -1)
			return (NULL);
		dir[i]->name = file->d_name;
		dir[i]->perms = find_modes(stats);
		dir[i]->links = stats->st_nlink;
		dir[i]->user = find_user(stats);
		dir[i]->group = find_group(stats);
		dir[i]->size = stats->st_size;
		dir[i]->timestamp = find_timestamp(stats);
		dir[i]->blocks = stats->st_blocks;
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
	while (j < size)
	{
		if (valid_arg(av[i]) == 1)
		{
			stats = (struct stat *)malloc(sizeof(struct stat));	
			if ((stat(av[i], stats)) == -1)
				return (NULL);
			dir[j]->name = av[i];
			dir[j]->perms = find_modes(stats);
			dir[j]->links = stats->st_nlink;
			dir[j]->user = find_user(stats);
			dir[j]->group = find_group(stats);
			dir[j]->size = stats->st_size;
			dir[j]->timestamp = find_timestamp(stats);
			dir[j]->blocks = stats->st_blocks;
			free(stats);
			j++;
		}
	i++;
	}
	return (dir);
}

void	sort_dir(t_file **dir, int size)
{
	int	i;
	t_file	*tmp;

	i = 0;
	while (i < size)
	{
		if (i < size - 1 && ft_strcmp(dir[i]->name, dir[i + 1]->name) > 0)
		{
			tmp = dir[i];
			dir[i] = dir[i + 1];
			dir[i + 1] = tmp;
			i -= 2;
		}
		i++;
	}
}

void	reverse_dir(t_file **dir, int size)
{
	int	i;
	t_file	*tmp;

	i = size;
	while (i >= 0)
	{
		if ((i > 0 && i < size) && ft_strcmp(dir[i]->name, dir[i - 1]->name) > 0)
		{
			tmp = dir[i];
			dir[i] = dir[i - 1];
			dir[i - 1] = tmp;
			i += 2;
		}
		i--;
	}
}
