/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 17:14:02 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:23:41 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Copy a certain amount of bytes from one place to another. In case destination
 * and source overlap, special caution is applied so that the copy is done in a
 * non-destructive manner.
 * @param *dest		A pointer to the destination of the copy
 * @param *src		A pointer to the place to copy from
 * @param n			The maximum amount of bytes to copy
 * @return			A pointer to the destination of the copy
 */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char		*src_cpy;
	char			*dest_cpy;

	if (dest == NULL && src == NULL)
		return (NULL);
	src_cpy = src;
	dest_cpy = dest;
	if (dest < src)
	{
		while (n > 0)
		{
			*dest_cpy = *src_cpy;
			dest_cpy++;
			src_cpy++;
			n--;
		}
		return (dest);
	}
	while (n > 0)
	{
		dest_cpy[n - 1] = src_cpy[n - 1];
		n--;
	}
	return (dest);
}
