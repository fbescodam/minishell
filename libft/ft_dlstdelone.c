/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dlstdelone.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 18:20:50 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/25 22:58:58 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_dlstdelone(t_ditem *item, void (*del)(void *))
{
	if (item)
	{
		(*del)(item->content);
		free(item);
	}
}
