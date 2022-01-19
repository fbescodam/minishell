/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/19 22:19:30 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/20 00:01:02 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../utils.h"
#include "builtins.h"

int	mini_exit(t_cmd *cmd)
{
	printf("exit\n");
	if (char_array_len(cmd->params) > 1)
	{
		printf("minishell: exit codes are not implemented (not required)\n");
	}
	exit_shell_w_error(-2);
	return (0);
}
