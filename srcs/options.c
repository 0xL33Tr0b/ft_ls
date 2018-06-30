#include "ft_ls.h"

void		fill_options(t_options *options, char *arg)
{
	int i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'l' && arg[i] != 'R' && arg[i] != 'a' 
				&& arg[i] != 'r' && arg[i] != 't')
			illegal_option(arg[i]);
		if(arg[i] == 'l')
			options->l = 1;
		if(arg[i] == 'R')
			options->R = 1;
		if(arg[i] == 'a')
			options->a = 1;
		if(arg[i] == 'r')
			options->r = 1;
		if(arg[i] == 't')
			options->t = 1;
		i++;
	}
	return ;
}

t_options	*init_options(int ac, char **av)
{
	int		i;
	int		tmp;
	t_options	*options;

	i = 1;
	options = (t_options *)malloc(sizeof(t_options));
	options->l = 0;
	options->R = 0;
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

int		option_l(t_file **dir, int filesize, t_options *options, t_padding *pad, int files)
{
	int i;

	i = -1;
	if (dir == NULL)
		return (1);
	if (filesize > 1 && files == 0)
		print_blocks(dir, filesize, options);
	while (++i < filesize)
	{
		if (!(options->a == 0 && dir[i]->name[0] == '.'))
			if (dir[i]->error != 1337)
				print_l(dir[i], pad);
	}
	if (options->R)
		option_R(dir, filesize, options);
	return (0);
}

void		no_padding(t_file **dir, int size, t_options *options)
{
	int i;

	i = -1;
	if (dir == NULL)
		return ;
	while (++i < size)
		if (!(options->a == 0 && dir[i]->name[0] == '.'))
			if (dir[i]->error != 1337)
				ft_putendl(dir[i]->name);
	if (options->R)
		option_R(dir, size, options);
}

void		option_R(t_file **dir, int size, t_options *options)
{
	int 	i;
	char	*path;

	i = -1;
	while (++i < size)
	{
		path = ft_strjoin(dir[0]->path, dir[i]->name);
		if (!(options->a == 0 && dir[i]->name[0] == '.'))
		{
			if (ft_strcmp(dir[i]->name, "./") > 0 && dir[i]->perms[0] == 'd')
			{
				ft_putchar('\n');
				ft_putstr(dir[0]->path);
				ft_putstr(dir[i]->name);
				ft_putstr(":\n");
				if (dir[i]->error != EACCES)
					neutral_ls(valid_path(path), options);
				else
					perm_denied(dir[i]->name);
			}
		}
		ft_strdel(&path);
	}
}

void		handle_options(t_file **dir, int size, t_options *options, t_padding *pad, int files)
{
	if (options->l == 1)
		option_l(dir, size, options, pad, files);
	else
		no_padding(dir, size, options);
}	
