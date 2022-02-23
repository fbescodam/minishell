/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_va_add.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 17:31:09 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/23 21:45:35 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/**
 * Add a pointer to memory to a ft_va_list (the memory gets duplicated)
 * @param[in] list		The list to append to
 * @param[in] index		The index to store the pointer at
 * @param[in] item		The item to duplicate and put into the list
 * @param[in] size		The size of memory to copy for the duplication (WARNING:
 * 						for strings, include the EOF character in the size!!)
 * @return				Returns NULL on error, a pointer to the duplicated
 * 						item on success
 */
t_ft_va_item	*ft_va_add(t_ft_va_list list, size_t index, void *item,
							size_t size)
{
	t_ft_va_item	*dup;

	dup = (t_ft_va_item *)malloc(sizeof(t_ft_va_item));
	if (!dup)
		return (NULL);
	dup->size = size;
	if (size > 0)
	{
		dup->item = malloc(size);
		if (!dup->item)
			return (ft_free((void *)dup));
		ft_memcpy(dup->item, item, size);
	}
	else
		dup->item = NULL;
	list[index] = dup;
	return (dup);
}
