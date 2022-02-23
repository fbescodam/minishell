/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_va_start.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 17:04:36 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/23 21:46:17 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Get the first item from a ft_va_list
 * @param[in] item	A pointer to a pointer to set to the first item
 * @param[in] list	The ft_va_list to get the first item from
 */
void	ft_va_start(t_ft_va_list *item, t_ft_va_list list)
{
	*item = list;
}
