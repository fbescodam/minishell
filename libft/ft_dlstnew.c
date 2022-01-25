/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dlstnew.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 18:07:34 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/25 23:07:19 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Allocate a new, empty double linked list
 * @return t_dlist*
 */
t_dlist	*ft_dlstnew(void)
{
	return ((t_dlist *)ft_calloc(1, sizeof(t_dlist)));
}
