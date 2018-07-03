/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 20:29:46 by rdurst            #+#    #+#             */
/*   Updated: 2018/07/03 20:31:46 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	count_args - returns the number of args after
**		the options
*/

int		count_args(char **av, int begin)
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
**	count_dirs - counts valid dirs in **av
*/

int		count_dirs(char **av, int begin)
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
**	count_files - counts valid files in **av
*/

int		count_files(char **av, int begin)
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
