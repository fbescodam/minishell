/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strhash.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 23:50:59 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/08 19:48:05 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/**
 * Hash a string using Jenkin's one_at_a_time algorithm, useful for lookup
 * @param[in] str The string to hash
 * @param[in] length The length of the string (the full string is not always needed)
 * @return The hashed string in unsigned integer format
 */
unsigned int	ft_strhash(const char *str, size_t length)
{
	size_t			i;
	unsigned int	hash;

	i = 0;
	hash = 0;
	while (i < length)
	{
		hash += str[i];
		hash += hash << 10;
		hash ^= hash >> 6;
		i++;
	}
	hash += hash << 3;
	hash ^= hash >> 11;
	hash += hash << 15;
	return (hash);
}
