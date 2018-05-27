/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 16:13:57 by rdurst            #+#    #+#             */
/*   Updated: 2018/05/17 17:54:14 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*find_filetype(struct stat *file)
{
	if (S_ISREG(file->st_mode) == 1)
		return ("File");
	if (S_ISDIR(file->st_mode) == 1)
		return ("Directory");
	if (S_ISSOCK(file->st_mode) == 1)
		return ("Socket");
	if (S_ISLNK(file->st_mode) == 1)
		return ("Symbolic link");
	else
		return ("?");
}

char 	*find_modes(struct stat *file)
{
	char *ret;

	ret = ft_strnew(10);
	ret[0] = (S_ISDIR(file->st_mode) ? 'd' : '-');
	ret[1] = (file->st_mode & S_IRUSR ? 'r' : '-');
	ret[2] = (file->st_mode & S_IWUSR ? 'w' : '-');
	ret[3] = (file->st_mode & S_IXUSR ? 'x' : '-');
	ret[4] = (file->st_mode & S_IRGRP ? 'r' : '-');
	ret[5] = (file->st_mode & S_IWGRP ? 'w' : '-');
	ret[6] = (file->st_mode & S_IXGRP ? 'x' : '-');
	ret[7] = (file->st_mode & S_IROTH ? 'r' : '-');
	ret[8] = (file->st_mode & S_IWOTH ? 'w' : '-');
	ret[9] = (file->st_mode & S_IXOTH ? 'x' : '-');
	return (ret);
}

char	*valid_path(char *path)
{
	int i;

	i = 0;
	while (path[i])
		i++;
	if (i == 0 || path[i] == '/')
		return (path);
	else
		return (ft_strjoin(path, "/"));
}

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
		dir = fill_dir(dir, size, name);
	if (options->r)
		reverse_dir(dir, size);
	else
		sort_dir(dir, size);
	padding = fill_padding(padding, dir, size);
	handle_options(dir, size, options, padding, 0);
	return (0);
}

void	treat_args(char **av, int begin, t_options *options)
{
	single_files_ls(av, begin, options);
	treat_dirs(av, begin, options);
}

int	count_dirs(char **av, int begin)
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

int	count_files(char **av, int begin)
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

void	treat_dirs(char **av, int begin, t_options *options)
{
	int i;
	int dirs;
	int files;

	i = begin;
	files = count_files(av, begin);
	dirs = count_dirs(av, begin);
	if (files > 0 && dirs > 0)
		ft_putchar('\n');
	while(av[i])
	{
		if (valid_arg(av[i]) == 2)
		{
			if (dirs > 1 || files > 0)
			{
				ft_putstr(av[i]);
				ft_putendl(":");
			}
			neutral_ls(valid_path(av[i]), options);
			if (valid_arg(av[i + 1]) == 2)
				ft_putchar('\n');
		}
		i++;
	}
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
