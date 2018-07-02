/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 12:40:29 by rdurst            #+#    #+#             */
/*   Updated: 2018/07/02 13:19:22 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	find_modes - returning a char * with
**	permissions from file in format 'drwx------'
*/

char	*find_modes(struct stat *file)
{
	char *ret;

	ret = ft_strnew(10);
	if (S_ISLNK(file->st_mode))
		ret[0] = 'l';
	else
		ret[0] = S_ISDIR(file->st_mode) ? 'd' : '-';
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

/*
**	find_error - returning errno from file accessing
*/

int		find_error(char *file)
{
	struct stat	*stats;
	DIR			*dir;

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

/*
**	find_user - returning user from stats
**	or itoaed one in case of failure
*/

char	*find_user(struct stat *stats)
{
	struct passwd	*usr;
	char			*ret;

	if ((usr = getpwuid(stats->st_uid)) == NULL)
		ret = ft_itoa(stats->st_uid);
	else
		ret = ft_strdup(usr->pw_name);
	if (ret == NULL)
		return (NULL);
	return (ret);
}

/*
**	find_group - returning group from stats
**	or itoaed one in case of failure
*/

char	*find_group(struct stat *stats)
{
	struct group	*grp;
	char			*ret;

	if ((grp = getgrgid(stats->st_gid)) == NULL)
		ret = ft_itoa(stats->st_gid);
	else
		ret = ft_strdup(grp->gr_name);
	if (ret == NULL)
		return (NULL);
	return (ret);
}

/*
**	find_link - returning the path contained by the symlink
**	or NULL if there is no one
*/

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
