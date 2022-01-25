/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dlstadd_back.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 18:29:35 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/25 18:31:44 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_back(t_dlist *list, t_ditem *item)
{
	t_ditem	*last;

	if (list->size > 0)
	{
		last = ft_dlstlast(list);
		last->next = item;
		item->prev = last;
		item->next = NULL;
	}
	else
	{
		item->prev = NULL;
		item->next = NULL;
		list->first = item;
	}
	list->size += 1;
}
