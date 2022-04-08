/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jgalloni <jgalloni@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/02 17:50:29 by jgalloni      #+#    #+#                 */
/*   Updated: 2022/04/08 23:05:15 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	malloc_empty_string(char **str)
{
	*str = ft_strdup("");
	if (!*str)
		return (-1);
	else
		return (0);
}

int	gnl_reset(char *buff)
{
	ft_bzero(buff, 100);
	return (0);
}
