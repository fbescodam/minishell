/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_realloc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/07 18:12:09 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:25:29 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Reallocate memory and free the old allocation
 * @param *ptr			The pointer to copy from
 * @param old_size		The size of the memory allocation to be freed
 * @param new_size		The size of the memory allocation to be allocated
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
