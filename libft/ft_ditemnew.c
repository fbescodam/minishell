/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ditemnew.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 21:50:20 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/25 21:52:01 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ditem	*ft_ditemnew(void *content)
{
	t_ditem	*item;

	item = ft_calloc(1, sizeof(t_ditem));
	if (item)
		item->content = content;
	return (item);
}
