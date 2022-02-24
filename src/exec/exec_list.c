#include "structs.h"
#include "debug.h"
#include "execute.h"
#include "error_handling.h"
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

void	handler()
{
	printf("\n");
}

void	fork_process(t_cmd *cmd, t_mini *mini)
{
	int		pid;
	int		status;
	int		terminated_process;

	terminated_process = 0;
	pid = fork();
	
	if (pid == -1)
		force_exit(mini, TOO_MANY_PROC);
	signal(SIGINT, handler);
	if (pid == 0)
		child_process(cmd);
	cmd->pid = pid;
	return ;
} 

int		execute_command(t_list *cmd_inst, t_mini *mini)
{
	int		ret;
	t_cmd 	*cmd;

	cmd = cmd_inst->content;
	ret = check_command(cmd, mini);
	if (ret == -2)
		return (-1);
	if (cmd->pipe_out[0])
	{
		ret = pipe(cmd->pipe_out);
		if (ret < 0)
			force_exit(mini, errno);
		((t_cmd *)((cmd_inst->next)->content))->pipe_in[0] = cmd->pipe_out[0];
		((t_cmd *)((cmd_inst->next)->content))->pipe_in[1] = cmd->pipe_out[1];
	}
	fork_process(cmd, mini);
	return (0);
}

int		execute_list(t_mini *mini)
{
	t_list	*current;
	int		ret;
	t_cmd	*cmd;
	int		amount;
	int		status;

	current = mini->cmds;
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
	while (amount)
	{
		ret = wait(&status);
		amount--;
	}
	if (((status) & 0x7f) == 0)
		mini->status = ((status) & 0xff00) >> 8;
	return (0);
}
