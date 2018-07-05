/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   majorminor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 13:19:34 by rdurst            #+#    #+#             */
/*   Updated: 2018/07/05 01:48:02 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*find_majmin(struct stat *stats)
{
	char *ret;

	if (!S_ISCHR(stats->st_mode) && !S_ISBLK(stats->st_mode))
		return (ft_itoa(stats->st_size));
	else
	{
		ret = ft_strjoin(ft_itoa(major(stats->st_rdev)), ", ");
		ret = ft_strjoin(ret, ft_itoa(minor(stats->st_rdev)));
		ret = ft_strjoin (ret, "\0");
	}
	return (ret);
}
