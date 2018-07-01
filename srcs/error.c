#include "ft_ls.h"

/*
	valid_arg - returning 2 if arg is a directory
		  - returning 1 if arg is a file
		  - returning 0 if arg cannot be
		     accessed or doesnt exist
*/

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

/*
	perm_denied - printing EACCES permission error
*/

void	perm_denied(char *file)
{
			ft_putstr("ft_ls: ");
			ft_putstr(file);
			ft_putstr(": Permission denied\n");
}

/*
	not_permitted - printing EAPERM permission error
*/

void	not_permitted(char *file)
{
	ft_putstr("ft_ls: ");
	ft_putstr(file);
	ft_putendl(": Operation not permitted");
}

/*
	illegal_option - printing usage
	in case of invalid options
*/

void	illegal_option(char option)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(option);
	ft_putchar('\n');
	ft_putendl("usage: ./ft_ls [-lRart] [file ...]");
	exit(-1);
}

/*
	no_such_file - printing missing file error
*/

void	no_such_file(char *file)
{
	ft_putstr("ft_ls: ");
	ft_putstr(file);
	ft_putstr(": No such file or directory\n");
}
