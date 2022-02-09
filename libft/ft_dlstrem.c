/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dlstrem.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 18:23:38 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/09 15:57:00 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Remove one item from a double linked list at a certain position
 * @param[in] item The item to remove from the linked list
 * @param[in] index The index of the item to remove
 */
void	ft_dlstrem(t_dlist *list, t_ditem *item, void (*del)(void *))
{
	if (item->prev)
		item->prev->next = item->next;
	if (item->next)
		item->next->prev = item->prev;
	list->size--;
	ft_dlstdelone(item, del);
}
