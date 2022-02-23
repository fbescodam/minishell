/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strxjoin.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 16:23:26 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/23 21:47:29 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "libft.h"

static char	*xerror(t_ft_va_list strs, char *res)
{
	ft_va_end(strs);
	ft_free(res);
	return (NULL);
}

static void	xjoin(size_t amount, t_ft_va_list strs, char *res)
{
	t_ft_va_list	strx;
	char			*temp;
	size_t			i;

	i = 0;
	temp = res;
	ft_va_start(&strx, strs);
	while (i < amount)
	{
		ft_memcpy(temp, (*strx)->item, (*strx)->size - 1);
		ft_va_arg(&strx);
		i++;
		if (i < amount)
			temp += (*strx)->size - 1;
	}
}

/**
 * Join many strings into one big string
 * @param[in] amount	The amount of strings to join
 * @param[in] strs		Strings to join into the newly formed string,
 * 						stored in ft_va_list format. Warning: this list always
 * 						freed by ft_va_end after running this method.
 * @return				A pointer to the newly allocated joined string,
 * 						or NULL on error
 */
char	*ft_strxjoin(size_t amount, t_ft_va_list strs)
{
	t_ft_va_list	strx;
	size_t			i;
	size_t			joint_len;
	char			*res;

	res = NULL;
	if (amount == 0)
		return (xerror(strs, res));
	joint_len = 0;
	i = 0;
	ft_va_start(&strx, strs);
	while (i < amount)
	{
		joint_len += (*strx)->size - 1;
		ft_va_arg(&strx);
		i++;
	}
	res = (char *)malloc(joint_len + 1);
	res[joint_len] = '\0';
	if (joint_len > 0)
		xjoin(amount, strs, res);
	ft_va_end(strs);
	return (res);
}
