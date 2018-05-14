/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 04:12:34 by rdurst            #+#    #+#             */
/*   Updated: 2017/11/14 20:37:30 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *list;
	t_list *tmp;

	list = *alst;
	while (list)
	{
		tmp = list;
		del(list->content, list->content_size);
		list = list->next;
		free(tmp);
	}
	*alst = NULL;
}
