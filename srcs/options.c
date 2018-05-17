#include "ft_ls.h"

void		fill_options(t_options *options, char *arg)
{
	int i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'l' && arg[i] != 'R' && arg[i] != 'a' 
				&& arg[i] != 'r' && arg[i] != 't')
		{
			ft_putstr("ft_ls: illegal option -- ");
			ft_putchar(arg[i]);
			ft_putchar('\n');
			ft_putendl("usage: ft_ls [-lRart] [file ...]");
			exit(-1);
		}
		if(arg[i] == 'l')
			options->l = 1;
		if(arg[i] == 'R')
			options->R = 1;
		if(arg[i] == 'a')
			options->a = 1;
		if(arg[i] == 'r')
			options->r = 1;
		if(arg[i] == 't')
			options->t = 1;
		i++;
	}
	return ;
}

t_options	*init_options(int ac, char **av)
{
	int		i;
	t_options	*options;

	i = 1;
	options = malloc(sizeof(t_options));
	options->l = 0;
	options->R = 0;
	options->a = 0;
	options->r = 0;
	options->t = 0;
	while (i < ac && av[i][0] == '-')
		fill_options(options, av[i++]);
	return (options);
}

int		option_l(char *filename, char *path, t_padding *pad)
{
	struct group	*grp;
	struct passwd	*usr;
	char			*perms;
	char			*timestamp;
	struct stat		*buf;
	int				ret;

	buf = malloc(sizeof(struct stat));
	ret = 0;

	if ((ret = stat(ft_strjoin(valid_path(path), filename), buf)) == -1)
	{
		printf("ft_ls: %s%s", filename, ": No such file or directory\n");
		return (1);
	}
	perms = find_modes(buf);
	usr = getpwuid(buf->st_uid);
	grp = getgrgid(buf->st_gid);
	timestamp = ctime(&buf->st_mtime);
	timestamp[24] = '\0';
	ft_putstr(perms);
	print_spaces(pad->links - ft_nbrlen(buf->st_nlink) + 1);
	ft_putnbr(buf->st_nlink);
	print_spaces(pad->user - ft_strlen(usr->pw_name));
	ft_putstr(usr->pw_name);
	print_spaces(pad->group - ft_strlen(grp->gr_name) + 1);
	ft_putstr(grp->gr_name);
	print_spaces(pad->size - ft_nbrlen(buf->st_size) + 1);
	ft_putnbr(buf->st_size);
	print_spaces(0);
	ft_putstr(timestamp);
	print_spaces(0);
	ft_putendl(filename);
	ft_strdel(&perms);
	free(buf);
	return (0);
}

int		no_options(char *filename, char *path)
{
	struct stat		*buf;
	int				ret;

	buf = malloc(sizeof(struct stat));
	ret = 0;

	if ((ret = stat(ft_strjoin(valid_path(path), filename), buf)) == -1)
	{
		printf("ft_ls: %s%s", filename, ": No such file or directory\n");
		return (1);
	}
	ft_putstr(filename);
	ft_putchar('\n');
	free(buf);
	return (0);
}

void		handle_options(char *name, char *path, t_options *options, t_padding *pad)
{
	if (options->l == 1)
		option_l(name, path, pad);
	else
		no_options(name, path);
}
