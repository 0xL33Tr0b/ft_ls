#include "ft_ls.h"

void	print_blocks(t_file **dir, int size)
{
	int ret;
	int i;

	i = 0;
	ret = 0;
	while (i < size)
		ret += dir[i++]->blocks;
	ft_putstr("total ");
	ft_intendl(ret);
}
