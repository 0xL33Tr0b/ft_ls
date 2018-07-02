/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 16:31:22 by rdurst            #+#    #+#             */
/*   Updated: 2018/07/02 11:11:58 by rdurst           ###   ########.fr       */
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

/*
**	structure for storing options
*/

typedef struct		s_options
{
	int				l;
	int				rec;
	int				a;
	int				r;
	int				t;
}					t_opts;

/*
**	structure for storing the width
**	of the fields in '-l'
*/

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
}					t_pad;

/*
**	structure for storing all
**	the fields of a directory
**	or a file
*/

typedef struct		s_file
{
	char			*path;
	char			*name;
	char			*perms;
	int				links;
	char			*linkpath;
	char			*user;
	char			*group;
	long			size;
	long			timestamp;
	long			ntimestamp;
	long			blocks;
	int				error;
}					t_file;

char				*find_filetype(struct stat *file);
char				*find_modes(struct stat *file);
int					option_l(t_file **d, int s, t_opts *o, t_pad *p, int f);
void				option_t(t_file **dir, int size);
void				no_padding(t_file **dir, int size, t_opts *options);
void				opts(t_file **d, int size, t_opts *o, t_pad *p, int f);
char				*valid_path(char *path);
int					ls(char *name, t_opts *options);
t_opts				*init_opts(int ac, char **av);
void				fill_opts(t_opts *options, char *arg);
t_pad				*init_pad(void);
t_pad				*fill_pad(t_pad *padding, t_file **dir, int size);
void				print_spaces(int nb);
int					ft_dirlen(char *name, char *path);
t_file				**init_dir(t_file **dir, int size);
char				*find_user(struct stat *stats);
char				*find_group(struct stat *stats);
char				*find_link(char *path, char *name);
int					find_error(char *file);
void				print_timestamp(long timestamp);
t_file				**fill_dir(t_file **d, int s, char *p, t_opts *o);
t_file				**sfiles(char **av, int b, int s, t_file **d, t_opts *o);
int					valid_arg(char *arg);
void				print_blocks(t_file **dir, int size, t_opts *options);
void				sort_dir(t_file **dir, int size);
void				reverse_dir(t_file **dir, int size);
void				option_t(t_file **dir, int size);
void				treat_args(char **av, int begin, t_opts *options);
void				treat_dirs(char **av, int begin, t_opts *options);
int					count_dirs(char **av, int begin);
int					count_files(char **av, int begin);
int					single_files_ls(char **av, int begin, t_opts *options);
void				sort_args(char **av, int begin);
void				reverse_args(char **av);
void				sort_by_time(char **av, int begin);
void				option_rec(t_file **dir, int size, t_opts *options);
void				free_file(t_file *dir);
void				free_dir(t_file **dir, int size);
int					next_dir_offset(char **av);
long				get_timestamp(char *dir);
void				not_permitted(char *file);
void				perm_denied(char *file);
void				illegal_option(char option);
void				no_such_file(char *file);
void				print_l(t_file *file, t_pad *pad);

#endif
