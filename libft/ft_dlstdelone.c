/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dlstdelone.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 18:20:50 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/08 19:48:05 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/**
 * Free a double linked list item and run a function on its contents
 * @param[in] item The item to free
 * @param[in] del The function to run on its contents (useful for freeing them)
 */
void	ft_dlstdelone(t_ditem *item, void (*del)(void *))
{
	if (item)
	{
		(*del)(item->content);
		free(item);
	}
}
