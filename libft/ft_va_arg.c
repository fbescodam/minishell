/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_va_arg.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 17:04:45 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/23 21:46:38 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Get the next argument from a ft_va_list
 * @param[in] item	A pointer to the last item from the ft_va_list,
 * 							this pointer gets set to the next one
 */
void	ft_va_arg(t_ft_va_list *item)
{
	*item += 1;
}
