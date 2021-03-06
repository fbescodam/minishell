/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 17:21:57 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/08 23:01:29 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "error_handling.h"
#include "utils.h"
#include "envars.h"

static int	exit_err(int is_child, t_cmd *cmd, char *str)
{
	if (is_child)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": numeric argument required", 2);
		return (0);
	}
	force_exit(cmd->mini, 255);
	return (0);
}

int	mini_exit(int is_child, t_cmd *cmd)
{
	char	*temp;

	if (is_child)
		ft_putendl_fd("exit", 2);
	if (char_array_len(cmd->params) > 1)
	{
		temp = cmd->params[1];
		while (*temp)
		{
			if (!ft_isdigit(*temp) && *temp != '-')
				break ;
			temp++;
		}
		if (!*temp)
		{
			if (is_child)
				return (0);
			cmd->mini->status = (int)(unsigned char)ft_atoi(cmd->params[1]);
		}
		else
			return (exit_err(is_child, cmd, cmd->params[1]));
	}
	force_exit(cmd->mini, cmd->mini->status);
	return (0);
}
