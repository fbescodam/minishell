/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_stralloc.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/09 00:34:12 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/09 00:37:06 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * @brief Allocate memory for a string. This allocation is NULL-terminated,
 * but not emptied (not filled with NULL characters).
 * @param[in] size The size of the allocation (NULL / '\0' not included)
 * @return A pointer to the allocated memory, or NULL on error
 */
char	*ft_stralloc(size_t size)
{
	char	*str;

	str = (char *)malloc(size + 1);
	if (str)
		str[size] = '\0';
	return (str);
}
