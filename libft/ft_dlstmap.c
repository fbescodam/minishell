/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dlstmap.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 21:48:31 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/29 20:50:13 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Create a copy of a double linked list and apply a method to every element
 * @param *lst					The double linked list to copy
 * @param void *(*f)(void *)	The method to apply to every element of the
 * 								copied list
 * @param void (*del)(void *)	The method applied to every element before
 * 								deletion (of the copy) if anything goes wrong
 * @return						The copied list after the applied method
 */
t_dlist	*ft_dlstmap(t_dlist *list, void *(*f)(void *), void (*del)(void *))
{
	t_dlist	*new_list;
	t_ditem	*old_elem;
	t_ditem	*new_elem;
	size_t	i;

	new_list = ft_dlstnew();
	if (!new_list)
		return (NULL);
	i = 0;
	old_elem = list->first;
	while (i < list->size)
	{
		new_elem = ft_ditemnew((*f)(old_elem->content));
		if (!new_elem)
		{
			ft_dlstclear(new_list, del);
			return (NULL);
		}
		ft_dlstadd_back(new_list, new_elem);
		old_elem = old_elem->next;
		i++;
	}
	return (new_list);
}
