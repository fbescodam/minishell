/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnlen.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 17:25:27 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:53:34 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Get the length of a string but stop counting at a certain amount of
 * characters
 * @param *s		The string to count the characters of
 * @size_t maxlen	The maximum length to return
 * @return			The length of the string or maxlen
 * 					if the real length > maxlen
 */
size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	i;

	i = 0;
	while (i < maxlen && s[i] != '\0')
		i++;
	return (i);
}
