/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_front.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/03 17:14:57 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/08 19:48:05 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Add an element to the front of a linked list
 * @param[in] **lst		The list to add the element to, can be NULL
 * @param[in] *new		The element to add to the list
 */
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (*lst)
		new->next = *lst;
	*lst = new;
}
