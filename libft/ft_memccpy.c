/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 16:31:33 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:22:52 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Copy a precise amount of bytes from one pointer to the other, or until
 * the character c is come across. Source and destination should not overlap.
 * @param *dest		The destination of the copy
 * @param *src		The source to copy from
 * @param c			The character at which to stop copying
 * @param n			The maximum amount of bytes to copy
 * @return			A pointer to destination, or NULL if n == 0
 */
void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char		*dest_cpy;
	const char	*src_cpy;

	dest_cpy = dest;
	src_cpy = src;
	while (n > 0)
	{
		*dest_cpy = *src_cpy;
		dest_cpy++;
		if (*src_cpy == (unsigned char)c)
			return ((void *)dest_cpy);
		src_cpy++;
		n--;
	}
	return (NULL);
}
