/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dlstrem.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 18:23:38 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/25 23:08:16 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Remove one item from a double linked list at a certain position
 * @param list The list to remove the item from
 * @param index The index of the item to remove
 */
void	ft_dlstrem(t_dlist *list, size_t index, void (*del)(void *))
{
	t_ditem		*item;

	item = ft_dlstget(list, index);
	if (!item)
		return ;
	item->prev->next = item->next;
	item->next->prev = item->prev;
	ft_dlstdelone(item, del);
}
