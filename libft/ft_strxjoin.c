/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strxjoin.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 16:23:26 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/09 16:48:39 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "libft.h"

static char	*xerror(va_list params, char *res)
{
	va_end(params);
	ft_free(res);
	return (NULL);
}

static char	*xinner(va_list params, char **res)
{
	char	*strx;
	char	*temp;

	strx = va_arg(params, char *);
	if (!strx)
		return (xerror(params, *res));
	temp = ft_strjoin(*res, strx);
	if (!temp)
		return (xerror(params, *res));
	free(*res);
	*res = temp;
	return (*res);
}

char	*ft_strxjoin(size_t amount, char *str1, char *str2, ...)
{
	va_list	params;
	size_t	i;
	char	*res;

	if (amount < 1)
		return (NULL);
	if (amount < 2)
		return (ft_strdup(str1));
	res = ft_strjoin(str1, str2);
	if (!res)
		return (NULL);
	va_start(params, str2);
	i = 2;
	while (i < amount)
	{
		if (xinner(params, &res) == NULL)
			return (NULL);
		i++;
	}
	va_end(params);
	return (res);
}
