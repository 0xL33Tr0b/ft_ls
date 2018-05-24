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

	if ((ret = ctime(&stats->st_mtime)) == NULL)
		return (NULL);
	ret[24] = '\0';
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

t_file	**fill_file(t_file **dir, char *name)
{
	struct stat *stats;

	stats = (struct stat *)malloc(sizeof(struct stat));	
	if ((stat(name, stats)) == -1)
		return (NULL);
	dir[0]->name = name;
	dir[0]->perms = find_modes(stats);
	dir[0]->links = stats->st_nlink;
	dir[0]->user = find_user(stats);
	dir[0]->group = find_group(stats);
	dir[0]->size = stats->st_size;
	dir[0]->timestamp = find_timestamp(stats);
	dir[0]->blocks = stats->st_blocks;
	free(stats);
	return (dir);
}
