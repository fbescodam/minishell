/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 13:37:33 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:49:32 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Compare two strings but not more than a certain amount of characters
 * @param *s1		A string to compare
 * @param *s2		Another string to compare
 * @size_t n		The maximum amount of characters to compare
 * @return			The difference between the two characters found at any
 * 					difference (0 if both strings are equal)
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && i < n - 1)
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
