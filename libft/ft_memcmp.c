/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 19:07:21 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:23:16 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Compare byte strings of the same length
 * @param *s1		A string to compare
 * @param *s2		Another string to compare
 * @param n			The maximum amount of bytes to compare
 * @return			The difference between the two bytes found at any
 * 					difference (0 if both strings are equal)
 */

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_cpy;
	const unsigned char	*s2_cpy;

	s1_cpy = s1;
	s2_cpy = s2;
	while (n > 0)
	{
		if (*s1_cpy != *s2_cpy)
			return (*s1_cpy - *s2_cpy);
		s1_cpy++;
		s2_cpy++;
		n--;
	}
	return (0);
}
