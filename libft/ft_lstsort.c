/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsort.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/07 16:41:18 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:22:34 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	swap_lst_content(t_list *a, t_list *b)
{
	void	*temp;

	temp = a->content;
	a->content = b->content;
	b->content = temp;
}

/**
 * Sort a linked list
 * @param **lst						The list to sort
 * @param (*f)(void *, void *)		The method to apply to sort the list, should
 * 									return 1 if the first item is bigger than
 * 									the second
 */
void	ft_lstsort(t_list **lst, int (*f)(void *, void *))
{
	size_t	size;
	t_list	*item;
	size_t	i;
	size_t	j;

	size = ft_lstsize(*lst);
	i = 0;
	while (i < size - 1)
	{
		j = 0;
		item = *lst;
		while (j < size - i - 1)
		{
			if ((*f)(item->content, item->next->content))
				swap_lst_content(item, item->next);
			item = item->next;
			j++;
		}
		i++;
	}
}
