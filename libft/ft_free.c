/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 19:45:17 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/08 19:48:05 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/**
 * Free a variable and set it to NULL
 * @param[in] *freeable		The variable to free and set to NULL
 * @return				Always returns NULL
 */
void	*ft_free(void *freeable)
{
	if (freeable)
		free(freeable);
	freeable = NULL;
	return (NULL);
}
