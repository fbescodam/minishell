/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 15:10:24 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:57:20 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Trim a string on the left and the right, removing a set of characters,
 * into a newly allocated string
 * @param *s1	The string to trim
 * @param *set	A set of characters to remove from the string at the beginning
 * 				and end
 * @return		A pointer to the trimmed string
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	char			*dest;
	unsigned int	start;
	size_t			dest_len;
	size_t			s1_len;

	s1_len = ft_strlen(s1);
	start = 0;
	while (s1[start] != '\0')
	{
		if (ft_strchr(set, (int)s1[start]))
			start++;
		else
			break ;
	}
	dest_len = s1_len - (size_t)start;
	while (s1_len > 0)
	{
		if (ft_strchr(set, (int)s1[s1_len]))
			dest_len--;
		else
			break ;
		s1_len--;
	}
	dest = ft_substr(s1, start, dest_len + 1);
	return (dest);
}
