/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 13:18:29 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/08 19:48:05 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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

	res = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (res)
	{
		i = 0;
		while (s[i] != '\0')
		{
			res[i] = (*f)(i, s[i]);
			i++;
		}
		res[i] = '\0';
	}
	return (res);
}
