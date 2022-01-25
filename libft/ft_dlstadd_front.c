/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dlstadd_front.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 18:15:59 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/25 23:00:13 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Add an item to the front of a double linked list
 * @param list The list to prepend to
 * @param item The item to add
 */
void	ft_dlstadd_front(t_dlist *list, t_ditem *item)
{
	item->next = list->first;
	item->prev = NULL;
	if (list->first != NULL)
		list->first->prev = item;
	list->first = item;
	list->size += 1;
}
