/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstget.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/22 18:34:28 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/22 18:50:20 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Get an item from a linked list at index
 * @param *lst	The list to go through
 * @param index	The index of the item to find
 */
t_list	*ft_lstget(t_list *lst, size_t index)
{
	t_list	*temp;

	temp = lst;
	while (index > 0)
	{
		temp = temp->next;
		if (!temp)
			return (NULL);
		index--;
	}
	return (temp);
}
