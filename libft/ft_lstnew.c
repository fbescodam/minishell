/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/03 17:05:37 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:22:16 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Create a new linked list element with content
 * @param *content		A pointer to the content to add to the element
 * @return				The created element, NULL on failure
 */
t_list	*ft_lstnew(void *content)
{
	t_list	*ret;

	ret = (t_list *)malloc(sizeof(t_list));
	if (ret)
	{
		ret->content = content;
		ret->next = NULL;
	}
	return (ret);
}
