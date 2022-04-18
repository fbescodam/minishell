/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tabs.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jgalloni <jgalloni@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/18 20:50:32 by jgalloni      #+#    #+#                 */
/*   Updated: 2022/04/18 21:01:19 by jgalloni      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	count_tabs(char *str)
{
	size_t	amount;
	size_t	i;

	i = 0;
	amount = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			amount++;
		i++;
	}
	return (amount);
}

static void	replace_tabs_w_spaces(char *str, char *temp)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		temp[j] = str[i];
		if (str[i] == '\t')
		{
			ft_memset((void *)&temp[j], ' ', 4);
			j += 3;
		}
		j++;
		i++;
	}
}

int	replace_tabs(char **prompt)
{
	char	*temp;
	size_t	amount;

	amount = count_tabs(*prompt);
	if (amount == 0)
		return (1);
	temp = ft_calloc(ft_strlen(*prompt) + 3 * amount + 1, sizeof(char));
	if (!temp)
		return (0);
	replace_tabs_w_spaces(*prompt, temp);
	free(*prompt);
	*prompt = temp;
	return (1);
}
