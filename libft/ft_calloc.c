/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 21:00:09 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/08 19:48:05 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/**
 * Allocate memory and clear it before returning it
 * @param[in] nmemb		The amount of elements to allocate for
 * @param[in] size		The size of the elements to allocate for
 * @return			The allocated memory, NULL on failure
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	size_t			size_to_malloc;

	if (nmemb == 0)
		nmemb = 1;
	if (size == 0)
		size = 1;
	size_to_malloc = size * nmemb;
	ptr = malloc(size_to_malloc);
	if (ptr)
		ft_bzero(ptr, size_to_malloc);
	return (ptr);
}
