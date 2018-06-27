#include "ft_ls.h"

int	valid_arg(char *arg)
{
	DIR		*dir;
	struct stat	*stats;

	stats = NULL;
	if ((dir = opendir(arg)) != NULL)
	{
		(void)closedir(dir);
		return (2);
	}
	stats = malloc(sizeof(struct stat));
	if (lstat(arg, stats) == -1)
		return (0);
	free(stats);
	return (1);
}

void	perm_denied(t_file **dir, int size)
{
	int i;
	int valid;
	int trig;

	i = -1;
	valid = 0;
	trig = 0;
	while (++i < size)
		if (dir[i]->user != NULL)
			valid++;
	i = -1;
	while (++i < size)
		if (dir[i]->user == NULL && dir[i]->size != -1)
		{
			if (trig == 0 && valid > 0)
				ft_putchar('\n');
			trig = 1;
			ft_putstr("ft_ls: ");
			ft_putstr(dir[i]->name);
			ft_putstr(": Permission denied\n");
		}
}

void	not_permitted(char *file)
{
	ft_putstr("ft_ls: ");
	ft_putstr(file);
	ft_putendl(": Operation not permitted");
}

void	illegal_option(char option)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(option);
	ft_putchar('\n');
	ft_putendl("usage: ./ft_ls [-lRart] [file ...]");
	exit(-1);
}

void	no_such_file(char *file)
{
	ft_putstr("ft_ls: ");
	ft_putstr(file);
	ft_putstr(": No such file or directory\n");
}
