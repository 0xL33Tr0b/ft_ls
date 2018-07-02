/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 16:13:57 by rdurst            #+#    #+#             */
/*   Updated: 2018/07/02 13:19:07 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	ls - handling all structures for a directory
*/

int		ls(char *name, t_opts *options)
{
	t_pad	*padding;
	int		size;
	t_file	**dir;

	dir = NULL;
	if (valid_arg(name) == 0 || valid_arg(name) == 1)
		return (1);
	padding = init_pad();
	size = ft_dirlen(name, "");
	dir = init_dir(dir, size);
	if (valid_arg(name) == 2)
		dir = fill_dir(dir, size, name, options);
	sort_dir(dir, size);
	if (options->t)
		option_t(dir, size);
	if (options->r)
		reverse_dir(dir, size);
	padding = fill_pad(padding, dir, size);
	opts(dir, size, options, padding, 0);
	free_dir(dir, size);
	return (0);
}

/*
**	single_files_ls - handling all structures
**	for the single files from char **av
*/

int		single_files_ls(char **av, int begin, t_opts *options)
{
	t_pad	*padding;
	int		size;
	t_file	**dir;

	dir = NULL;
	padding = init_pad();
	size = count_files(av, begin);
	dir = init_dir(dir, size);
	dir = sfiles(av, begin, size, dir, options);
	sort_dir(dir, size);
	if (options->t)
		option_t(dir, size);
	if (options->r)
		reverse_dir(dir, size);
	padding = fill_pad(padding, dir, size);
	opts(dir, size, options, padding, 1);
	return (0);
}

/*
**	main - where the program starts,
**	calling single_file_ls or ls regarding the args
*/

int		main(int ac, char **av)
{
	int		counter;
	t_opts	*options;

	counter = 1;
	options = init_opts(ac, av);
	while (av[counter] && av[counter][0] == '-')
		counter++;
	if ((ac - counter) == 0)
		return (ls("./", options));
	if ((ac - counter) > 0)
		treat_args(av, counter, options);
	exit(1);
}
