/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dlstlast.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 18:28:08 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/25 18:33:11 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ditem	*ft_dlstlast(t_dlist *list)
{
	if (list->size > 0)
		return (ft_dlstget(list, list->size - 1));
	return (NULL);
}
