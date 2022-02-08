/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_realloc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/07 18:12:09 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/08 19:48:05 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/**
 * Reallocate memory and free the old allocation
 * @param[in] *ptr			The pointer to copy from
 * @param[in] old_size		The size of the original memory allocation to copy
 * @param[in] new_size		The size of the memory allocation to be allocated
 * @return				The address of the newly allocated memory
 */
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		new_size = 1;
	if (new_size < old_size)
		return (ptr);
	new_ptr = malloc(new_size);
	if (ptr && new_ptr)
		ft_memmove(new_ptr, ptr, old_size);
	if (ptr)
		free(ptr);
	return (new_ptr);
}
