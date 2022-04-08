/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envar_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/09 00:18:29 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/09 00:30:34 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include <stdlib.h>

static size_t	get_amount_of_exported_envars(t_dlist *envars)
{
	size_t	i;
	size_t	amount;
	t_ditem	*item;

	item = envars->first;
	i = 0;
	amount = 0;
	while (i < envars->size)
	{
		if (((t_envar *)item->content)->export)
			amount++;
		item = item->next;
		i++;
	}
	return (amount);
}

char	**get_envars_as_envp(t_mini *mini)
{
	size_t			i;
	size_t			amount;
	t_ditem			*item;
	char			**ret;

	i = 0;
	amount = get_amount_of_exported_envars(mini->envars);
	item = mini->envars->first;
	ret = (char **)ft_calloc(amount + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	while (item)
	{
		if (((t_envar *)item->content)->export)
		{
			ret[i] = ((t_envar *)item->content)->export;
			i++;
		}
		item = item->next;
	}
	return (ret);
}

int	is_valid_env_name_char(size_t pos, char c)
{
	if (pos == 0)
	{
		if (c != '_' && !ft_isalpha(c))
			return (0);
	}
	else if (c != '_' && !ft_isalnum(c))
		return (0);
	return (1);
}

int	join_parsed_str(char **parsed_str, char *str)
{
	char	*temp;

	temp = ft_strjoin(*parsed_str, str);
	if (!temp)
		return (0);
	free(*parsed_str);
	*parsed_str = temp;
	return (1);
}
