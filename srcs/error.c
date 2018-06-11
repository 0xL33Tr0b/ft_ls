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
