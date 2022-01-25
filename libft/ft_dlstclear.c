/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dlstclear.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 18:12:34 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/25 23:04:21 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/**
 * Clear a double linked list and free the entirity of its existence
 * @param list The list to free
 * @param del A function to use to free the contents of the list items
 */
void	ft_dlstclear(t_dlist *list, void (*del)(void *))
{
	t_ditem		*item;
	t_ditem		*next_item;

	if (list)
	{
		item = list->first;
		while (item)
		{
			next_item = item->next;
			del(item);
			item = next_item;
		}
		free(list);
	}
}
