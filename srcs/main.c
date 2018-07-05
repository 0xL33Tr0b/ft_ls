/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 16:13:57 by rdurst            #+#    #+#             */
/*   Updated: 2018/07/05 01:48:26 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	ls - handling all structures for a directory
*/

int		ls(char *name, t_opts *options)
{
	t_pad	*padding;
	t_info	info;
	t_file	**dir;

	dir = NULL;
	if (valid_arg(name) == 0 || valid_arg(name) == 1)
		return (1);
	padding = init_pad();
	info.size = ft_dirlen(name, "");
	info.type = 0;
	dir = init_dir(dir, info.size);
	if (valid_arg(name) == 2)
		dir = fill_dir(dir, info, name);
	sort_dir(dir, info.size);
	if (options->t)
		option_t(dir, info.size);
	if (options->r)
		reverse_dir(dir, info.size);
	padding = fill_pad(padding, dir, info.size);
	opts(dir, info, options, padding);
	free_dir(dir, info.size);
	free(padding);
	return (0);
}

/*
**	single_files_ls - handling all structures
**	for the single files from char **av
*/

int		single_files_ls(char **av, t_opts *options)
{
	t_pad	*padding;
	t_info	info;
	t_file	**dir;

	dir = NULL;
	info.size = count_files(av);
	if (info.size > 0)
	{
		info.type = 1;
		padding = init_pad();
		dir = init_dir(dir, info.size);
		dir = sfiles(av, info, dir);
		sort_dir(dir, info.size);
		if (options->t)
			option_t(dir, info.size);
		if (options->r)
			reverse_dir(dir, info.size);
		padding = fill_pad(padding, dir, info.size);
		opts(dir, info, options, padding);
		free_dir(dir, info.size);
		free(padding);
	}
	return (0);
}

/*
**	opts - calls -l or not
*/

void	opts(t_file **dir, t_info info, t_opts *options, t_pad *pad)
{
	if (options->l == 1)
		option_l(dir, info, options, pad);
	else
		no_opts(dir, info, options);
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
	options = init_opts(&av[1]);
	while (av[counter] && av[counter][0] == '-')
		counter++;
	if ((ac - counter) == 0)
		ls("./", options);
	if ((ac - counter) > 0)
		treat_args(&av[counter], options);
	free(options);
	exit(0);
}
