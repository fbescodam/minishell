/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dlstrem.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 18:23:38 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/25 21:47:31 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstrem(t_dlist *list, size_t index)
{
	t_ditem		*item;

	item = ft_dlstget(list, index);
	if (!item)
		return ;
	item->prev->next = item->next;
	item->next->prev = item->prev;
	ft_dlstdelone(item);
}
