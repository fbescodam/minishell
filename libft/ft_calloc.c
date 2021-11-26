/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 21:00:09 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:19:24 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Allocate memory and clear it before returning it
 * @param nmemb		The amount of elements to allocate for
 * @param size		The size of the elements to allocate for
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
