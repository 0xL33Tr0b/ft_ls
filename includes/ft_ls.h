/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 16:31:22 by rdurst            #+#    #+#             */
/*   Updated: 2018/05/17 17:45:00 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <sys/stat.h>
# include <stdio.h>
# include <time.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <dirent.h>
# include "../libft/libft.h"

typedef struct		s_options
{
	int				l;
	int				R;
	int				a;
	int				r;
	int				t;
}					t_options;

typedef struct		s_padding
{
	int				directory_number;
	int				perms;
	int				links;
	int				user;
	int				group;
	int				size;
	int				timestamp;
	int				name;
}					t_padding;

typedef struct		s_file
{
	char			*name;
	char			*perms;
	int				links;
	char			*user;
	char			*group;
	int				size;
	char			*timestamp;
}					t_file;

char				*find_filetype(struct stat *file);
char				*find_modes(struct stat *file);
int					print_file_info(char *filename, char *path);
char				*valid_path(char *path);
int					neutral_ls(char *name, t_options *options);
t_options			*init_options(int ac, char **av);
void				fill_options(t_options *options, char *arg);
t_padding			*init_padding(void);
t_padding			*fill_padding(t_padding *padding, char *filename, char *path);

#endif
