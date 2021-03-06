/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   char_array_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 17:21:57 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/18 17:01:32 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

/**
 * @brief Counts and returns how many strings in an array of type char **
 */
size_t	char_array_len(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	add_string_to_array(char ***to, char *from)
{
	size_t	arr_size;
	char	**temp;
	int		i;

	if (!from)
		return (-1);
	i = 0;
	arr_size = char_array_len(*to);
	temp = ft_calloc(arr_size + 2, sizeof(char *));
	if (!temp)
		return (ENOMEM);
	while ((*to)[i])
	{
		temp[i] = (*to)[i];
		i++;
	}
	ft_free(*to);
	temp[i] = from;
	temp[i + 1] = 0;
	*to = temp;
	return (0);
}
