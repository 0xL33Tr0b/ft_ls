#include "ft_ls.h"

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

char	*find_user(struct stat *stats)
{
	struct passwd	*usr;
	char		*ret;

	if ((usr = getpwuid(stats->st_uid)) == NULL)
		ret = ft_itoa(stats->st_uid);
	else
		ret = ft_strdup(usr->pw_name);
	if (ret == NULL)
		return (NULL);
	return (ret);
}

char	*find_group(struct stat *stats)
{
	struct group	*grp;
	char		*ret;

	if ((grp = getgrgid(stats->st_gid)) == NULL) 
		ret = ft_itoa(stats->st_gid);
	else 
		ret = ft_strdup(grp->gr_name);
	if (ret == NULL)
		return (NULL);
	return (ret);
}

char	*find_link(char *path, char *file)
{
	char *buf;
	char *tmp;
	
	buf = (char *)malloc(sizeof(char) * 1024);
	buf[1023] = '\0';
	tmp = ft_strdup(path);
	path = ft_strjoin(tmp, file);
	if (readlink(path, buf, 1024) == -1)
		return (NULL);
	return (buf);
}

void	print_timestamp(long timestamp)
{
	char *ret;

	if ((ret = (char *)malloc(sizeof(char) * 24)) == NULL)
		return ;
	if ((ret = ctime_r(&timestamp, ret)) == NULL)
	{
		ft_strdel(&ret);
		return ;
	}
	ret[16] = '\0';
	ft_putstr(ret);
	ft_strdel(&ret);
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
			dir[i]->name = ft_strdup(file->d_name);
			dir[i]->perms = find_modes(stats);
			if (options->l)
			{
				ft_putstr("ft_ls: ");
				ft_putstr(dir[i]->name);
				ft_putendl(": Operation not permitted");
			}
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

void	sort_dir(t_file **dir, int size)
{
	int	i;
	t_file	*tmp;

	i = 0;
	while (i < size - 1)
	{
		if(ft_strcmp(dir[i]->name, dir[i + 1]->name) > 0)
		{
			tmp = dir[i];
			dir[i] = dir[i + 1];
			dir[i + 1] = tmp;
			if (i > 0)
				i -= 1;
		}
		else
			i++;
	}
}

void	reverse_dir(t_file **dir, int size)
{
	int	i;
	t_file	*tmp;

	i = 0;
	size--;
	while (i < size)
	{
		tmp = dir[i];
		dir[i] = dir[size];
		dir[size] = tmp;
		i++;
		size--;
	}
	return ;
}

void	option_t(t_file **dir, int size)
{
	int	i;
	t_file	*tmp;

	i = 0;
	while (i < size - 1)
	{
		if (dir[i]->timestamp < dir[i + 1]->timestamp 
		|| (dir[i]->timestamp == dir[i + 1]->timestamp 
		&& dir[i]->ntimestamp < dir[i + 1]->ntimestamp))
		{
			tmp = dir[i];
			dir[i] = dir[i + 1];
			dir[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}
