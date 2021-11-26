/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 15:00:32 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:26:11 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Join two strings together into a newly allocated string
 * @param *s1	The string to start with
 * @param *s2	The string to end with
 * @return		A pointer to the joined string
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	dest = (char *)malloc(s1_len + s2_len + 1);
	if (dest)
	{
		ft_memcpy(dest, s1, s1_len);
		ft_memcpy(dest + s1_len, s2, s2_len + 1);
	}
	return (dest);
}
