#include "ft_ls.h"

void		fill_options(t_options *options, char *arg)
{
	int i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'l' && arg[i] != 'R' && arg[i] != 'a' 
				&& arg[i] != 'r' && arg[i] != 't')
		{
			ft_putstr("ft_ls: illegal option -- ");
			ft_putchar(arg[i]);
			ft_putchar('\n');
			ft_putendl("usage: ft_ls [-lRart] [file ...]");
			exit(-1);
		}
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
	t_options	*options;

	i = 1;
	options = malloc(sizeof(t_options));
	options->l = 0;
	options->R = 0;
	options->a = 0;
	options->r = 0;
	options->t = 0;
	while (i < ac && av[i][0] == '-')
		fill_options(options, av[i++]);
	return (options);
}
