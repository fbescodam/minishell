/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reserved_cmds.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/05 17:50:19 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/19 23:26:54 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "builtins/builtins.h"
#	include <stdio.h>

/**
 * @brief Check if given command is a reserved keyword for minishell and if it
 * is, run it.
 * @param cmd Command struct
 * @return Returns -1 if no reserved keyword, 0 if it was and it completed
 * successfully, > 0 on system error (using errno), < 0 on minishell error
 */
int	check_run_reserved_cmds(t_cmd *cmd)
{
	if (ft_strncmp("cd\0", cmd->params[0], 3) == 0)
		return (mini_cd(cmd));
	if (ft_strncmp("exit\0", cmd->params[0], 5) == 0)
		return (mini_exit(cmd));
	if (ft_strncmp("pwd\0", cmd->params[0], 4) == 0)
		return (mini_pwd(cmd));
	if (ft_strncmp("echo\0", cmd->params[0], 5) == 0)
		return (mini_echo(cmd));
	return (-1);
}

int	is_reserved(t_cmd *cmd)
{
	if (ft_strncmp("cd\0", cmd->params[0], 3) == 0)
		return (1);
	if (ft_strncmp("exit\0", cmd->params[0], 5) == 0)
		return (1);
	if (ft_strncmp("pwd\0", cmd->params[0], 4) == 0)
		return (1);
	if (ft_strncmp("echo\0", cmd->params[0], 5) == 0)
		return (1);
	return (0);
}
