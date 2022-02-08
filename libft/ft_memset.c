/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 15:29:31 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/08 19:48:05 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Write a certain amount of the same byte to a specific place in memory
 * @param[in] *s	A pointer to the place to write to
 * @param[in] c		The byte value to write
 * @param[in] n		The amount of bytes to write
 * @return		The pointer to the place to write to
 */
void	*ft_memset(void *s, int c, size_t n)
{
	char	*copy;

	copy = s;
	while (n > 0)
	{
		*copy = c;
		copy++;
		n--;
	}
	return (s);
}
