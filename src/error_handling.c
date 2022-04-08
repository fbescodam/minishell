/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 17:21:10 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/08 23:27:17 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "readline/readline.h"
#include "structs.h"
#include "utils.h"
#include "custom_errors.h"

// will exit with mini->status if err == 0!
// it should not do this (why again?)
void	force_exit(t_mini *mini, int err)
{
	free_mini(mini);
	rl_clear_history();
	if (!err)
		exit(mini->status);
	else
		exit(err);
}

void	error_manager(t_mini *mini, int err)
{
	if (err == IGNORE)
		return ;
	mini->status = err;
	if (err == PARSE_ERROR)
		ft_putstr_fd("minishell: parse error\n", 2);
	else if (err == CMDNF)
		ft_putstr_fd("minishell: command not found\n", 2);
	else if (err == SEGF)
		ft_putstr_fd("minishell: !! SEGFAULT !!\n", 2);
	else if (err > 0)
		perror("minishell");
	else if (err == 0)
		ft_putstr_fd("minishell: an unknown error occurred (exit code 0?)", 2);
}
