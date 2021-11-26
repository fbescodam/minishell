/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 16:06:53 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:23:32 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Copy a certain amount of bytes from one place to another
 * @param *dest		A pointer to the place to copy to
 * @param *src		A pointer to the place to copy from
 * @param n			The maximum amount of bytes to copy
 * @return			A pointer to the place that has been copied to
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*dest_cpy;
	const char	*src_cpy;

	if (dest == NULL && src == NULL)
		return (NULL);
	dest_cpy = dest;
	src_cpy = src;
	while (n > 0)
	{
		*dest_cpy = *src_cpy;
		dest_cpy++;
		src_cpy++;
		n--;
	}
	return (dest);
}
