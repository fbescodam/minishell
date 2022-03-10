/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/15 18:46:07 by fbes          #+#    #+#                 */
/*   Updated: 2022/03/10 18:05:53 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Copy a string from one place in memory to another and make sure it's null-
 * terminated. If size = 3, it copies 2 characters and sets the 3rd to NULL.
 * @param[in] *dest		The place to copy to
 * @param[in] *src		The place to copy from
 * @param[in] size		The maximum amount of bytes to copy
 * @return			The length of the string the method tried to create
 */
size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	if (size != 0)
	{
		i = 0;
		while (i < size - 1 && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}
