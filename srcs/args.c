/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 13:35:13 by rdurst            #+#    #+#             */
/*   Updated: 2018/07/03 20:37:05 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	sort_args - sorting char **av by ASCII order
*/

void	sort_args(char **av, int begin)
{
	char	*tmp;
	int		i;

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
**	reverse_args - reversing char **av
*/

void	reverse_args(char **av)
{
	int		i;
	int		end;
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
**	sort_by_time - sorting char **av valid args
**		by time of last modification
*/

void	sort_by_time(char **av, int begin)
{
	int		i;
	int		nextdir;
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
**	treat_args - sends single files from **av to single_file_ls
**		   - calls **av sorting funcs referring to options
*/

void	treat_args(char **av, int begin, t_opts *options)
{
	single_files_ls(av, begin, options);
	if (options->t)
		sort_by_time(av, begin);
	if (options->r)
		reverse_args(&av[begin]);
	treat_dirs(av, begin, options);
}

/*
**	treat_dirs - sends valid dirs from **av to ls
*/

void	treat_dirs(char **av, int begin, t_opts *options)
{
	int		i;
	int		dirs;
	int		files;
	char	*path;

	i = begin;
	files = count_files(av, begin);
	dirs = count_dirs(av, begin);
	if (files > 0 && dirs > 0)
		ft_putchar('\n');
	while (av[i])
	{
		path = valid_path(av[i]);
		if (valid_arg(av[i]) == 2)
		{
			if (dirs > 1 || files > 0)
				two_points(av[i]);
			ls(path, options);
			if (valid_arg(av[i + 1]) == 2)
				ft_putchar('\n');
		}
		ft_strdel(&path);
		i++;
	}
}
