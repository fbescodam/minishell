/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 16:00:31 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/25 23:57:38 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/**
 * Clear memory of a certain size
 * @param *s	The memory to clear
 * @param n		The amount of memory to clear
 */
void	ft_bzero(void *s, size_t n)
{
	char	*s_copy;

	s_copy = s;
	while (n > 0)
	{
		*s_copy = '\0';
		s_copy++;
		n--;
	}
}
