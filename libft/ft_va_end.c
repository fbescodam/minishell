/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_va_end.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 17:04:43 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/23 21:46:44 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/**
 * Clean up a list
 * @param[in] list	The list to clean up and free memory from
 */
void	ft_va_end(t_ft_va_list list)
{
	t_ft_va_list	temp;

	ft_va_start(&temp, list);
	while (*temp)
	{
		ft_free((*temp)->item);
		free(*temp);
		ft_va_arg(&temp);
	}
	free(list);
}
