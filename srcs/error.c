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

void	perm_denied(char *file)
{
	ft_putstr("ft_ls: ");
	ft_putstr(file);
	ft_putstr(": Permission denied\n");
}
