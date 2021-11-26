/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 19:45:17 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:20:03 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Free a variable and set it to NULL
 * @param *freeable		The variable to free and set to NULL
 * @return				Always returns NULL
 */
void	*ft_free(void *freeable)
{
	if (freeable)
		free(freeable);
	freeable = NULL;
	return (NULL);
}
