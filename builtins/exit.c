/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/19 22:19:30 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/19 22:56:01 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../utils.h"
#include "builtins.h"

int	mini_exit(t_cmd *cmd)
{
	if (char_array_len(cmd->params) > 1)
	{
		printf("exit: too many arguments\n");
		return (-2);
	}
	exit_shell_w_error(-2);
	return (0);
}
