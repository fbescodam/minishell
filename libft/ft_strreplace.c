/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strreplace.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 21:25:13 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/08 21:40:54 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
	#include <stdio.h>

char	*ft_strreplace(char *str, char *find, char *replace)
{
	char	*replaced;
	char	*loc;
	size_t	find_len;
	size_t	old_len;
	size_t	repl_len;

	find_len = ft_strlen(find);
	old_len = ft_strlen(str);
	if (find_len == 0 || find_len > old_len)
		return (ft_strdup(str));
	loc = ft_strnstr(str, find, old_len);
	if (!loc)
	{
		printf("ft_strnstr failed! str: %s, find: %s, old_len: %lu\n", str, find, old_len);
		return (ft_strdup(str));
	}
	repl_len = ft_strlen(replace);
	replaced = malloc((old_len - find_len + repl_len + 1) * sizeof(char));
	if (!replaced)
		return (NULL);
	ft_memmove(replaced, str, loc - str);
	ft_memmove(&replaced[loc - str], replace, repl_len);
	ft_memmove(&replaced[loc - str + repl_len], &loc[find_len],
		ft_strlen(&loc[find_len]) + 1);
	return (replaced);
}
