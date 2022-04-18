/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_cmd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jgalloni <jgalloni@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 14:29:12 by jgalloni      #+#    #+#                 */
/*   Updated: 2022/04/18 19:34:59 by jgalloni      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "builtins.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/**
 * @return Returns 0 on no error, -2 on ENOMEM, -1 on command found
 */
static int	find_abs_path(t_cmd *cmd, t_mini *mini)
{
	int		i;

	i = 0;
	while (mini->paths[i])
	{
		cmd->path = ft_str3join(mini->paths[i], "/", *(cmd->params));
		if (!cmd->path)
			return (-2);
		if (access(cmd->path, R_OK) == 0)
			return (0);
		free(cmd->path);
		i++;
	}
	return (-1);
}

int	check_command(t_cmd *cmd, t_mini *mini)
{
	int		ret;

	if (!*(cmd->params))
		return (0);
	cmd->builtin = is_reserved(cmd);
	if (cmd->builtin != MINI_BUILTIN_NONE)
		return (0);
	if (ft_strchr(*(cmd->params), '/'))
	{
		if (access(*(cmd->params), R_OK) == 0)
		{
			cmd->path = ft_strdup(*(cmd->params));
			return (0);
		}
		return (-1);
	}
	ret = find_abs_path(cmd, mini);
	if (ret == -1)
		cmd->path = NULL;
	return (ret);
}
