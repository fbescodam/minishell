/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dlstget.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 18:24:10 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/25 23:06:11 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Get an item from a double linked list at a certain index position
 * @param list The list to get the item from
 * @param index The index to look for
 * @return The item at the specified index
 */
t_ditem	*ft_dlstget(t_dlist *list, size_t index)
{
	t_ditem	*item;

	if (index >= list->size)
		return (NULL);
	item = list->first;
	while (index > 0)
	{
		item = item->next;
		index--;
	}
	return (item);
}
