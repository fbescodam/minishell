/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 17:24:40 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/08 19:48:05 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Find a character in memory
 * @param[in] *s	The memory to start searching from
 * @param[in] c		The character to search for
 * @param[in] n		The maximum amount of bytes to check
 * @return		The character found, if not found then NULL
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		c_cpy;
	const unsigned char	*s_cpy;

	c_cpy = c;
	s_cpy = s;
	while (n > 0)
	{
		if (*s_cpy == c_cpy)
			return ((void *)s_cpy);
		s_cpy++;
		n--;
	}
	return (NULL);
}
