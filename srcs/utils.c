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

int	single_files_ls(char **av, int begin, t_options *options)
{
	t_padding	*padding;
	int 		size;
	t_file		**dir = NULL;

	padding = init_padding();
	size = count_files(av, begin);
	dir = init_dir(dir, size);
	dir = fill_files(av, begin, size, dir);
	if (options->r == 1)
		reverse_dir(dir, size);
	else
		sort_dir(dir, size);
	padding = fill_padding(padding, dir, size);
	handle_options(dir, size, options, padding, 1);
	return (0);
}

void	sort_args(char **av, int begin)
{
	char	*tmp;
	int 	i;

	i = begin;
	while (av[begin])
	{
		if (av[begin + 1])
			if (ft_strcmp(av[begin], av[begin + 1]) > 0)
			{
				tmp = av[begin];
				av[begin] = av[begin + 1];
				av[begin + 1] = tmp;
				begin = i;
			}
		begin++;
	}
	return ;
}

void	reverse_args(char **av, int begin)
{
	int	i;
	int	end;
	char	*tmp;

	i = begin;
	while (av[i])
		i++;
	end = i;
	while (i >= begin)
	{
		if (av[i] && av[i - 1])
			if (ft_strcmp(av[i], av[i - 1]) > 0)
			{
				tmp = av[i];
				av[i] = av[i - 1];
				av[i - 1] = tmp;
				i = end;
			}
		i--;
	}
	return ;
}
