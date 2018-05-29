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
	sort_dir(dir, size);
	if (options->t)
		option_t(dir, size);
	if (options->r)
		reverse_dir(dir, size);
	padding = fill_padding(padding, dir, size);
	handle_options(dir, size, options, padding, 1);
	return (0);
}

int	count_args(char **av, int begin)
{
	int i;
	int ret;

	i = begin;
	ret = 0;
	while (av[i++])
		ret++;
	return (ret);
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

void	reverse_args(char **av)
{
	int	i;
	int	end;
	char	*tmp;
	
	i = 0;
	end = 0;
	while (av[end])
		end++;
	end--;
	while (i < end)
	{
		tmp = av[i];
		av[i] = av[end];
		av[end] = tmp;
		i++;
		end--;
	}
	return ;
}

long	get_timestamp(char *dir)
{
	struct stat	*stats;

	stats = malloc(sizeof(struct stat));
	if (stat(dir, stats) == -1)
		return (0);
	return (stats->st_mtime);
}

int	next_dir_offset(char **av)
{
	int ret;

	ret = 1;
	while (av[ret] && valid_arg(av[ret]) != 2)
		ret++;
	if (valid_arg(av[ret]) == 2)
		return (ret);
	else
		return (0);
}

void	sort_by_time(char **av, int begin)
{
	int	i;
	int	nextdir;
	char	*tmp;

	i = begin;
	nextdir = 0;
	while (av[i])
	{
		if (valid_arg(av[i]) == 2 && (nextdir = next_dir_offset(&av[i])) != 0)
			if (get_timestamp(av[i]) < get_timestamp(av[i + nextdir]))
			{
				tmp = av[i];
				av[i] = av[i + nextdir];
				av[i + nextdir] = tmp;
				i = begin;
			}
		i++;
	}
}
