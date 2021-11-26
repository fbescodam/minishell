/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ptoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/11 00:19:48 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:24:18 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ptr_loop(char *ret, intptr_t ptr)
{
	static char	base[] = "0123456789abcdef";

	if (ptr != 0)
	{
		ptr_loop(ret - 1, ptr / 16);
		*ret = base[ptr % 16];
	}
}

/**
 * Convert a pointer to a string
 * @param ptr	A pointer
 * @return		The converted string
 */
char	*ft_ptoa(intptr_t ptr)
{
	char	*ret;
	int		num_len;

	num_len = ft_numlen(ptr, 16);
	ret = ft_calloc(num_len + 1, sizeof(char));
	if (!ret)
		return (NULL);
	if (ptr == 0)
		ret[0] = '0';
	else
		ptr_loop(ret + num_len - 1, ptr);
	return (ret);
}
