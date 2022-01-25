/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dlstget.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 18:24:10 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/25 21:56:29 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
