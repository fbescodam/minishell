/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/19 22:47:09 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/19 22:47:50 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../utils.h"
#include "builtins.h"

int	mini_cd(t_cmd *cmd)
{
	if (cmd->params[1])
		return (chdir(cmd->params[1]));
	else
		return (chdir(getenv("HOME")));
}
