/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/03 17:32:17 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:21:25 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Clear a linked list
 * @param **lst					The list to clear
 * @param void (*del)(void *)	A method to apply to every element before
 * 								freeing them, can be NULL
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp1;
	t_list	*temp2;

	if (lst)
	{
		temp1 = *lst;
		while (temp1)
		{
			temp2 = temp1->next;
			ft_lstdelone(temp1, del);
			temp1 = temp2;
		}
		*lst = NULL;
	}
}
