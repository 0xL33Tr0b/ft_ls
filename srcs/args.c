#include "ft_ls.h"

/*
	count_args - returns the number of args after
		the options
*/

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

/*
	sort_args - sorting char **av by ASCII order
*/

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

/*
	reverse_args - reversing char **av
*/

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

/*
	sort_by_time - sorting char **av valid args
		by time of last modification
*/

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

/*
	treat_args - sends single files from **av to single_file_ls
		   - calls **av sorting funcs referring to options
*/

void	treat_args(char **av, int begin, t_options *options)
{
	single_files_ls(av, begin, options);
	if (options->t)
		sort_by_time(av, begin);
	if (options->r)
		reverse_args(&av[begin]);
	treat_dirs(av, begin, options);
}

/*
	count_dirs - counts valid dirs in **av
*/

int	count_dirs(char **av, int begin)
{
	int dirs;
	int i;

	dirs = 0;
	i = begin;
	while (av[i])
	{
		if (valid_arg(av[i]) == 2)
			dirs++;
		i++;
	}
	return (dirs);
}

/*
	count_files - counts valid files in **av
*/

int	count_files(char **av, int begin)
{
	int files;
	int i;

	files = 0;
	i = begin;
	while (av[i])
	{
		if (valid_arg(av[i]) == 1)
			files++;
		i++;
	}
	return (files);
}

/*
	treat_dirs - sends valid dirs from **av to ls
*/

void	treat_dirs(char **av, int begin, t_options *options)
{
	int i;
	int dirs;
	int files;

	i = begin;
	files = count_files(av, begin);
	dirs = count_dirs(av, begin);
	if (files > 0 && dirs > 0)
		ft_putchar('\n');
	while(av[i])
	{
		if (valid_arg(av[i]) == 2)
		{
			if (dirs > 1 || files > 0)
			{
				ft_putstr(av[i]);
				ft_putendl(":");
			}
			ls(valid_path(av[i]), options);
			if (valid_arg(av[i + 1]) == 2)
				ft_putchar('\n');
		}
	i++;
	}
}
