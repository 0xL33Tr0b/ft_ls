/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 13:19:43 by rdurst            #+#    #+#             */
/*   Updated: 2018/07/03 20:59:20 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	fill_options - fills t_opts * from '-lRart'
*/

void	fill_options(t_opts *options, char *arg)
{
	int i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'l' && arg[i] != 'R' && arg[i] != 'a'
				&& arg[i] != 'r' && arg[i] != 't')
			illegal_option(arg[i]);
		if (arg[i] == 'l')
			options->l = 1;
		if (arg[i] == 'R')
			options->rec = 1;
		if (arg[i] == 'a')
			options->a = 1;
		if (arg[i] == 'r')
			options->r = 1;
		if (arg[i] == 't')
			options->t = 1;
		i++;
	}
	return ;
}

/*
**	init_opts - mallocing a t_opts *
*/

t_opts	*init_opts(int ac, char **av)
{
	int		i;
	int		tmp;
	t_opts	*options;

	i = 1;
	options = (t_opts *)malloc(sizeof(t_opts));
	options->l = 0;
	options->rec = 0;
	options->a = 0;
	options->r = 0;
	options->t = 0;
	while (i < ac && av[i][0] == '-')
		fill_options(options, av[i++]);
	sort_args(av, i);
	tmp = i;
	while (i < ac)
	{
		if (valid_arg(av[i]) == 0)
			no_such_file(av[i]);
		i++;
	}
	return (options);
}

/*
**	option_l - printing a t_file ** with -l
*/

int		option_l(t_file **dir, int size, t_opts *opts, t_pad *pad, int files)
{
	int i;

	i = -1;
	if (dir == NULL)
		return (1);
	if (size > 1 && files == 0)
		print_blocks(dir, size, opts);
	while (++i < size)
	{
		if (!(opts->a == 0 && dir[i]->name[0] == '.'))
			if (dir[i]->error != 1337)
				print_l(dir[i], pad);
	}
	if (opts->rec)
		option_rec(dir, size, opts);
	return (0);
}

/*
**	no_opts - prints a t_file ** without options
*/

void	no_opts(t_file **dir, int size, t_opts *options)
{
	int i;

	i = -1;
	if (dir == NULL)
		return ;
	while (++i < size)
		if (!(options->a == 0 && dir[i]->name[0] == '.'))
			if (dir[i]->error != 1337)
				ft_putendl(dir[i]->name);
	if (options->rec)
		option_rec(dir, size, options);
}

/*
**	option_rec - handles the -R listing all
**		directories recursively
*/

void	option_rec(t_file **dir, int size, t_opts *options)
{
	int		i;
	char	*path;
	char	*tmp;

	i = -1;
	while (++i < size)
	{
		path = ft_strjoin(dir[0]->path, dir[i]->name);
		tmp = valid_path(path);
		if (!(options->a == 0 && dir[i]->name[0] == '.'))
		{
			if (ft_strcmp(dir[i]->name, "./") > 0 && dir[i]->perms[0] == 'd')
			{
				ft_putchar('\n');
				ft_putstr(dir[0]->path);
				ft_putstr(dir[i]->name);
				ft_putstr(":\n");
				if (dir[i]->error != EACCES)
					ls(tmp, options);
				else
					perm_denied(dir[i]->name);
			}
		}
		ft_strdel(&path);
		ft_strdel(&tmp);
	}
}
