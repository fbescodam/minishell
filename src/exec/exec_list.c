/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_list.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jgalloni <jgalloni@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 20:06:29 by jgalloni      #+#    #+#                 */
/*   Updated: 2022/04/18 16:59:54 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "debug.h"
#include "execute.h"
#include "envars.h"
#include "builtins.h"
#include "utils.h"
#include "error_handling.h"
#include "signal_handling.h"
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

static void	fork_process(t_cmd *cmd, t_mini *mini)
{
	int		pid;

	if (cmd->heredoc != NULL)
		write_heredoc(cmd, mini);
	pid = fork();
	if (pid == -1)
		force_exit(mini, TOO_MANY_PROC);
	if (pid == 0)
		child_process(cmd);
	cmd->pid = pid;
	return ;
}

static int	execute_command(t_list *cmd_inst, t_mini *mini)
{
	int		ret;
	t_cmd	*cmd;

	cmd = cmd_inst->content;
	ret = check_command(cmd, mini);
	if (ret == -2)
		return (-1);
	if (cmd->pipe_out[0])
	{
		ret = pipe(cmd->pipe_out);
		if (ret < 0)
			force_exit(mini, errno);
		((t_cmd *)(cmd_inst->next)->content)->pipe_in[0] = cmd->pipe_out[0];
		((t_cmd *)(cmd_inst->next)->content)->pipe_in[1] = cmd->pipe_out[1];
	}
	fork_process(cmd, mini);
	return (0);
}

static void	set_exit_code(int *status, t_mini *mini)
{
	if (WIFSIGNALED(*status) && WTERMSIG(*status) == SIGSEGV)
	{
		set_mini_status(mini, SEGF);
		error_manager(mini, SEGF);
	}
	else if (WIFSIGNALED(*status) && WTERMSIG(*status) == SIGINT)
		set_mini_status(mini, 130);
	else if (WIFSIGNALED(*status) && WTERMSIG(*status) == SIGQUIT)
		set_mini_status(mini, 131);
	else if (!((*status) & 0x7f)
		&& !set_mini_status(mini, ((*status) & 0xff00) >> 8))
		error_manager(mini, ENOMEM);
}

void	wait_n_processes(int amount, t_mini *mini)
{
	int		ret;
	int		status;
	t_cmd	*cmd;

	while (amount)
	{
		ret = wait(&status);
		if (ret == -1)
			perror("minishell");
		else if (((status) & 0xff00) >> 8 == 0)
		{
			cmd = get_cmd_from_pid(mini->cmds, ret);
			if (cmd && cmd->builtin != MINI_BUILTIN_NONE
				&& !run_in_child_only(cmd->builtin))
			{
				if (run_reserved(0, cmd) != 0)
					force_exit(mini, ret);
			}
		}
		amount--;
	}
	set_exit_code(&status, mini);
}

int	execute_list(t_mini *mini)
{
	t_list	*current;
	int		ret;
	t_cmd	*cmd;
	int		amount;

	amount = 0;
	current = mini->cmds;
	signal(SIGINT, exec_sig_handler);
	signal(SIGQUIT, exec_sig_handler);
	while (current)
	{
		cmd = ((t_cmd *)(current->content));
		ret = execute_command(current, mini);
		if (cmd->pipe_in[0])
		{
			close(cmd->pipe_in[0]);
			close(cmd->pipe_in[1]);
		}
		if (ret < 0)
			return (ret);
		current = current->next;
		amount++;
	}
	wait_n_processes(amount, mini);
	return (0);
}
