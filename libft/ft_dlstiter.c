/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dlstiter.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 18:37:06 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/25 21:53:48 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
