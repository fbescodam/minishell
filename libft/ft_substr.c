/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 14:13:01 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:58:40 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Trim a string to a certain length into a newly allocated string
 * @param *s	The string to trim
 * @param start	The offset to start at
 * @param len	The maximum length of the trimmed string
 * @return		A pointer to the newly allocated, trimmed string
 */
char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;
	size_t	final_len;

	final_len = 0;
	if (start < ft_strlen(s))
	{
		final_len = ft_strlen(s) - (size_t)start;
		if (final_len > len)
			final_len = len;
	}
	dest = (char *)malloc(final_len + 1);
	if (dest)
	{
		i = 0;
		while (i < final_len)
		{
			dest[i] = s[(size_t)start + i];
			i++;
		}
		dest[i] = '\0';
	}
	return (dest);
}
