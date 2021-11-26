/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 20:10:12 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:55:33 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Search for a string in a string
 * @param *str		The string to search in
 * @param *sub		The string to find
 * @param len		The amount of characters to stop searching after
 * @return			A pointer to the string found, or NULL if not found
 */
char	*ft_strnstr(const char *str, const char *sub, size_t len)
{
	size_t	found_len;
	size_t	to_find_len;
	size_t	i;

	to_find_len = ft_strlen(sub);
	if (to_find_len == 0)
		return ((char *)str);
	found_len = 0;
	i = 0;
	while (str[i] != '\0' && i < len - to_find_len - 1)
	{
		if (str[i] == sub[found_len])
			found_len++;
		else if (found_len != to_find_len)
		{
			i = i - found_len;
			found_len = 0;
		}
		else
			break ;
		i++;
	}
	if (found_len == to_find_len)
		return ((char *)&str[i - found_len]);
	return (NULL);
}
