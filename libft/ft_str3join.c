/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str3join.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/05 23:08:26 by fbes          #+#    #+#                 */
/*   Updated: 2022/03/05 23:10:27 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/**
 * Join a path together
 * @param[in] str1 A string to join
 * @param[in] str2 A string to join
 * @param[in] str3 A string to join
 * @return A newly allocated string where the paths are glued together
 */
char	*ft_str3join(char *str1, char *str2, char *str3)
{
	char	*dest;
	size_t	str1_len;
	size_t	str2_len;
	size_t	str3_len;

	str1_len = ft_strlen(str1);
	str2_len = ft_strlen(str2);
	str3_len = ft_strlen(str3);
	dest = (char *)malloc(str1_len + str2_len + str3_len + 1);
	if (dest)
	{
		ft_memcpy(dest, str1, str1_len);
		ft_memcpy(dest + str1_len, str2, str2_len);
		ft_memcpy(dest + str1_len + str2_len, str3, str3_len + 1);
	}
	return (dest);
}
