#include "ft_ls.h"

char 	*find_modes(struct stat *file)
{
	char *ret;

	ret = ft_strnew(10);
	ret[0] = (S_ISLNK(file->st_mode) ? 'l' : (S_ISDIR(file->st_mode) ? 'd' : '-'));
	ret[1] = (file->st_mode & S_IRUSR ? 'r' : '-');
	ret[2] = (file->st_mode & S_IWUSR ? 'w' : '-');
	ret[3] = (file->st_mode & S_IXUSR ? 'x' : '-');
	ret[4] = (file->st_mode & S_IRGRP ? 'r' : '-');
	ret[5] = (file->st_mode & S_IWGRP ? 'w' : '-');
	ret[6] = (file->st_mode & S_IXGRP ? 'x' : '-');
	ret[7] = (file->st_mode & S_IROTH ? 'r' : '-');
	ret[8] = (file->st_mode & S_IWOTH ? 'w' : '-');
	ret[9] = (file->st_mode & S_IXOTH ? 'x' : '-');
	return (ret);
}

int	find_error(char *file)
{
	struct stat	*stats;
	DIR		*dir;

	dir = opendir(file);
	if (errno == EACCES)
		return (errno);
	if (dir != NULL)
		(void)closedir(dir);
	if ((stats = malloc(sizeof(struct stat))) == NULL)
		return (-1);
	lstat(file, stats);
	free(stats);
	return (errno);
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
	ft_putstr(ret + 4);
	ft_strdel(&ret);
}
