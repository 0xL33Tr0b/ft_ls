#include "ft_ls.h"

/*
	sort_dir - sorts a t_file ** by ASCII order
*/

void	sort_dir(t_file **dir, int size)
{
	int	i;
	t_file	*tmp;

	i = 0;
	while (i < size - 1)
	{
		if(ft_strcmp(dir[i]->name, dir[i + 1]->name) > 0)
		{
			tmp = dir[i];
			dir[i] = dir[i + 1];
			dir[i + 1] = tmp;
			if (i > 0)
				i -= 1;
		}
		else
			i++;
	}
}

/*
	reverse_dir - reverses a t_file **
*/

void	reverse_dir(t_file **dir, int size)
{
	int	i;
	t_file	*tmp;

	i = 0;
	size--;
	while (i < size)
	{
		tmp = dir[i];
		dir[i] = dir[size];
		dir[size] = tmp;
		i++;
		size--;
	}
	return ;
}

/*
	option_t - sorts a t_file ** by time of last modification
*/

void	option_t(t_file **dir, int size)
{
	int	i;
	t_file	*tmp;

	i = 0;
	while (i < size - 1)
	{
		if ((dir[i]->timestamp < dir[i + 1]->timestamp)
				|| (dir[i]->timestamp == dir[i + 1]->timestamp
					&& dir[i]->ntimestamp < dir[i + 1]->ntimestamp))
		{
			tmp = dir[i];
			dir[i] = dir[i + 1];
			dir[i + 1] = tmp;
			if (i > 0)
				i -= 1;
		}
		else
			i++;
	}
}
