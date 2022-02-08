/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strschr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 17:44:20 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/08 19:48:05 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Search for a character from a set in a string
 * @param[in] *str The string to search through
 * @param[in] *set The set of characters to look for
 * @return The first character from the set found
 */
char	*ft_strschr(char const *str, char const *set)
{
	char	*copy;

	copy = (char *)str;
	while (*copy)
	{
		if (ft_strchr(set, *copy))
			return (copy);
		copy++;
	}
	return (NULL);
}
