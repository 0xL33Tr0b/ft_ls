#include "ft_ls.h"

char	*find_filetype(struct stat *file)
{
	if (S_ISREG(file->st_mode) == 1)
		return ("File");
	if (S_ISDIR(file->st_mode) == 1)
		return ("Directory");
	if (S_ISSOCK(file->st_mode) == 1)
		return ("Socket");
	if (S_ISLNK(file->st_mode) == 1)
		return ("Symbolic link");
	else
		return ("?");
}

char 	*find_modes(struct stat *file)
{
	char *ret;

	ret = ft_strnew(10);
	ret[0] = (S_ISDIR(file->st_mode) ? 'd' : '-');
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
void	print_file_info(char *filename)
{
	struct group	*grp;
	struct passwd	*usr;
	char			*perms;
	char			*timestamp;
	struct stat		*buf;
	int				ret;

	buf = malloc(sizeof(struct stat));
	ret = 0;
	if ((ret = stat(filename, buf)) == -1)
		return ;
	perms = find_modes(buf);
	usr = getpwuid(buf->st_uid);
	grp = getgrgid(buf->st_gid);
	timestamp = ctime(&buf->st_mtime);
	timestamp[24] = '\0';
	printf("%s ", perms);
	printf("%d\t", buf->st_nlink);
	printf("%s ", usr->pw_name);
	printf("%s ", grp->gr_name);
	printf("%lld\t", buf->st_size);
	printf("%s ", timestamp);
	printf("%s\n", filename);
	ft_strdel(&perms);

}

int	main(int ac, char **av)
{
	DIR *current;
	struct dirent *file;

	if (ac == 1)
	{
		if ((current = opendir(".")) == NULL)
			return (1);
		while ((file = readdir(current)) != NULL)
			print_file_info(file->d_name);
		(void)closedir(current);
		return (0);
	}
	else if (ac == 2)
	{
		if ((current = opendir(av[1])) == NULL)
		{
			printf("ft_ls: %s%s", av[1], ": No such file or directory\n");
			return (1);
		}
		while ((file = readdir(current)) != NULL)
			print_file_info(file->d_name);
		(void)closedir(current);
		return (0);
	}
	else
		ft_putendl("Usage: ./ft_ls <directory>");
	return (0);
}
