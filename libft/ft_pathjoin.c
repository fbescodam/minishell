/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pathjoin.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/04 00:00:36 by fbes          #+#    #+#                 */
/*   Updated: 2022/03/04 00:08:03 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/**
 * Join a path together
 * @param[in] path1	First part of the path
 * @param[in] path2 Second part of the path
 * @return A newly allocated string where the paths are glued together with a /
 */
char	*ft_pathjoin(char *path1, char *path2)
{
	char	*dest;
	size_t	path1_len;
	size_t	path2_len;

	path1_len = ft_strlen(path1);
	path2_len = ft_strlen(path2);
	dest = (char *)malloc(path1_len + path2_len + 2);
	if (dest)
	{
		ft_memcpy(dest, path1, path1_len);
		dest[path1_len] = '/';
		ft_memcpy(dest + path1_len + 1, path2, path2_len + 1);
	}
	return (dest);
}
