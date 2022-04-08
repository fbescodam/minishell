/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 13:18:29 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/09 00:42:05 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Copy a string and apply a function to every byte
 * @param[in] *s						The string to copy
 * @param[in] (*f)(unsigned int, char)	The method to apply to every character,
 * 									where the unsigned int is the character's
 * 									position in the string and char is the
 * 									character
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*res;
	unsigned int	i;

	res = ft_stralloc(ft_strlen(s));
	if (res)
	{
		i = 0;
		while (s[i] != '\0')
		{
			res[i] = (*f)(i, s[i]);
			i++;
		}
	}
	return (res);
}
