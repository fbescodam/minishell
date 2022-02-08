/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 20:02:34 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/08 19:48:05 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Search for a character in a string, starting from the back
 * @param[in] *s	The string to search in
 * @param[in] c		The character to look for
 * @return		A pointer to the character in the string, NULL if not found
 */
char	*ft_strrchr(const char *s, int c)
{
	size_t		i;

	i = ft_strlen(s) + 1;
	while (i > 0)
	{
		if (s[i - 1] == c)
			return ((char *)&s[i - 1]);
		i--;
	}
	return (NULL);
}
