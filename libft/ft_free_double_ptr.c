/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_double_ptr.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 19:45:17 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/08 19:48:05 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * Free a double pointer and its contents, usually generated by ft_split
 * @param[in] **freeable	A double pointer to free
 * @return				Always returns NULL
 */
void	**ft_free_double_ptr(void **freeable)
{
	int		i;

	if (freeable)
	{
		i = 0;
		while (freeable[i])
		{
			free(freeable[i]);
			i++;
		}
		free(freeable);
	}
	freeable = NULL;
	return (NULL);
}
