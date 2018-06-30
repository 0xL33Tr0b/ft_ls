/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 16:13:57 by rdurst            #+#    #+#             */
/*   Updated: 2018/06/11 17:42:33 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		neutral_ls(char *name, t_options *options)
{
	t_padding		*padding;
	int			size;
	t_file			**dir = NULL;

	if (valid_arg(name) == 0 || valid_arg(name) == 1)
		return (1);
	padding = init_padding();
	size = ft_dirlen(name, "");
	dir = init_dir(dir, size);
	if (valid_arg(name) == 2)
		dir = fill_dir(dir, size, name, options);
	sort_dir(dir, size);
	if (options->t)
		option_t(dir, size);
	if (options->r)
		reverse_dir(dir, size);
	padding = fill_padding(padding, dir, size);
	handle_options(dir, size, options, padding, 0);
	free_dir(dir, size);
	return (0);
}

int	single_files_ls(char **av, int begin, t_options *options)
{
	t_padding	*padding;
	int 		size;
	t_file		**dir = NULL;

	padding = init_padding();
	size = count_files(av, begin);
	dir = init_dir(dir, size);
	dir = fill_files(av, begin, size, dir, options);
	sort_dir(dir, size);
	if (options->t)
		option_t(dir, size);
	if (options->r)
		reverse_dir(dir, size);
	padding = fill_padding(padding, dir, size);
	handle_options(dir, size, options, padding, 1);
	return (0);
}

int	main(int ac, char **av)
{
	int		counter;
	t_options	*options;

	counter = 1;
	options = init_options(ac, av);
	while (av[counter] && av[counter][0] == '-')
		counter++;
	if ((ac - counter) == 0)
		return (neutral_ls("./", options));
	if ((ac - counter) > 0)
		treat_args(av, counter, options);
	return (0);
}
