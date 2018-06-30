#include "ft_ls.h"

void	print_l(t_file *dir, t_padding *pad)
{
	ft_putstr(dir->perms);
	print_spaces(pad->links - ft_nbrlen(dir->links) + 1);
	ft_putnbr(dir->links);
	print_spaces(pad->user - ft_strlen(dir->user));
	ft_putstr(dir->user);
	print_spaces(pad->group - ft_strlen(dir->group) + 1);
	ft_putstr(dir->group);
	print_spaces(pad->size - ft_nbrlen(dir->size) + 1);
	ft_putnbr(dir->size);
	print_spaces(0);
	print_timestamp(dir->timestamp);
	print_spaces(0);
	ft_putstr(dir->name);
	if (dir->linkpath != NULL)
	{
		ft_putstr(" -> ");
		ft_putstr(dir->linkpath);
	}
	ft_putchar('\n');
}
