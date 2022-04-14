/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 17:21:57 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/14 21:34:23 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "envars.h"
#include "libft.h"
#include <errno.h>

int	mini_unset(int is_child, t_cmd *cmd)
{
	size_t	i;
	t_ditem	*to_unset;

	if (char_array_len(cmd->params) < 2)
		return (0);
	i = 1;
	while (cmd->params[i])
	{
		if (!is_valid_env_name(cmd->params[i]) && is_child)
			print_builtin_err("export", cmd->params[i],
				"not a valid identifier");
		else
		{
			to_unset = get_envar_item(cmd->mini->envars, cmd->params[i]);
			if (to_unset)
			{
				if (((t_envar *)to_unset->content)->hash == PATH_HASH && \
					!set_mini_paths(cmd->mini, ""))
					return (ENOMEM);
				ft_dlstrem(cmd->mini->envars, to_unset, &free_envar);
			}
		}
		i++;
	}
	return (0);
}
