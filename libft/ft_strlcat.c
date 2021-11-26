/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 14:36:46 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:26:18 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Copy and concatenate a string
 * @param *dest		The place to copy to
 * @param *src		The place to copy from
 * @param size		The maximum amount of bytes to copy
 * @return			The length of the string the method tried to create
 */
size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t		src_len;
	size_t		dest_len;
	size_t		i;

	src_len = ft_strlen(src);
	i = 0;
	while (dest[i] && i < size)
		i++;
	dest_len = i;
	while (src[i - dest_len] && i + 1 < size)
	{
		dest[i] = src[i - dest_len];
		i++;
	}
	if (dest_len < size)
		dest[i] = '\0';
	return (dest_len + src_len);
}
