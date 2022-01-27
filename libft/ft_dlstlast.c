/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dlstlast.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 18:28:08 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/25 23:06:52 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Get the last item of a double linked list
 * @param list The list to get the last item of
 * @return The last item
 */
t_ditem	*ft_dlstlast(t_dlist *list)
{
	if (list->size > 0)
		return (ft_dlstget(list, list->size - 1));
	return (NULL);
}
