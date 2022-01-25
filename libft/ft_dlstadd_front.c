/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dlstadd_front.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 18:15:59 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/25 18:20:24 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_front(t_dlist *list, t_ditem *item)
{
	item->next = list->first;
	item->prev = NULL;
	if (list->first != NULL)
		list->first->prev = item;
	list->first = item;
	list->size += 1;
}
