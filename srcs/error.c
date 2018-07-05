/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 12:48:11 by rdurst            #+#    #+#             */
/*   Updated: 2018/07/05 01:47:38 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	valid_arg - returning 2 if arg is a directory
**		  - returning 1 if arg is a file
**		  - returning 0 if arg cannot be
**		     accessed or doesnt exist
*/

int		valid_arg(char *arg)
{
	DIR			*dir;
	struct stat	*stats;
	int			ret;

	stats = NULL;
	ret = 0;
	if ((dir = opendir(arg)) != NULL)
	{
		(void)closedir(dir);
		return (2);
	}
	if ((stats = (struct stat *)malloc(sizeof(struct stat))) == NULL)
		ret = 0;
	if (lstat(arg, stats) == -1)
		ret = 0;
	else
		ret = 1;
	free(stats);
	return (ret);
}

/*
**	perm_denied - printing EACCES permission error
*/

void	perm_denied(char *file, t_info info)
{
	if (info.size > 1)
		ft_putchar('\n');
	ft_putstr_fd("./ft_ls: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
}

/*
**	not_permitted - printing EAPERM permission error
*/

void	not_permitted(t_file **dir, t_info info)
{
	int i;

	i = -1;
	while (++i < info.size)
		if (dir[i]->error == EPERM)
		{
			ft_putstr_fd("./ft_ls: ", STDERR_FILENO);
			ft_putstr_fd(dir[i]->name, STDERR_FILENO);
			ft_putstr_fd(": Operation not permitted\n", STDERR_FILENO);
		}
}

/*
**	illegal_option - printing usage
**	in case of invalid options
*/

void	illegal_option(char option)
{
	ft_putstr_fd("./ft_ls: illegal option -- ", STDERR_FILENO);
	ft_putchar_fd(option, STDERR_FILENO);
	ft_putstr_fd("\nusage: ./ft_ls [-lartR] [file ...]\n", STDERR_FILENO);
	exit(1);
}

/*
**	no_such_file - printing missing file error
*/

void	no_such_file(char *file)
{
	ft_putstr_fd("ls: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
}
