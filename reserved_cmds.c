/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reserved_cmds.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/05 17:50:19 by fbes          #+#    #+#                 */
/*   Updated: 2021/12/05 18:10:21 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#	include <stdio.h>

/**
 * @brief Check if given command is a reserved keyword for minishell and if it
 * is, run it.
 * @param cmd Command struct
 * @return Returns 1 if no reserved keyword, 0 if it was and it completed
 * successfully, < 0 on error
 */
int	check_run_reserved_cmds(t_cmd *cmd)
{
	if (ft_strncmp("cd\0", cmd->params[0], 3) == 0)
		return (chdir(cmd->params[1]));
	return (1);
}
