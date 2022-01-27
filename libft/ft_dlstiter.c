/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dlstiter.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 18:37:06 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/25 23:06:35 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Iterate over a double linked list, applying a function to every item
 * @param list The list to iterate over
 * @param f The function to apply to every item's contents
 */
void	ft_dlstiter(t_dlist *list, void (*f)(void *))
{
	t_ditem	*item;

	item = list->first;
	while (item)
	{
		(*f)(item->content);
		item = item->next;
	}
}
