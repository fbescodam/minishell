/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_va_new.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 17:29:32 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/23 21:46:50 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/**
 * Create a new ft_va_list of a certain size. The size should be the amount of
 * additional parameters a method requires, not the total amount of parameters.
 * @param[in] size	The amount of items to be put into the ft_va_list
 * @return			A newly allocated ft_va_list, or NULL on error
 */
t_ft_va_list	ft_va_new(size_t size)
{
	t_ft_va_list	list;

	list = (t_ft_va_list)ft_calloc(size + 1, sizeof(t_ft_va_item *));
	return (list);
}
