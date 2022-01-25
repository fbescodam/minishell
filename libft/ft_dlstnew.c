/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dlstnew.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 18:07:34 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/25 18:12:15 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstnew(void)
{
	return ((t_dlist *)ft_calloc(1, sizeof(t_dlist)));
}
