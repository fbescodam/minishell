/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ptrlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/02 19:55:52 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:24:30 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Get the amount of characters necessary to print a pointer
 * @param ptr	The pointer to check
 * @return		The amount of characters necessary to print it
 */
int	ft_ptrlen(intptr_t ptr)
{
	if (ptr < 0)
		return (ft_ptrlen(-ptr));
	if (ptr < 10)
		return (3);
	return (1 + ft_ptrlen(ptr / 16));
}
