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

int	fork_process(t_cmd *cmd, t_mini *mini)
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
	return (pid);
} 

int		execute_command(t_cmd *cmd, t_mini *mini)
{
	int		ret;

	ret = check_command(cmd, mini);
	if (ret == -2)
		return (-1);
	//print_command_status(cmd, ret);
	fork_process(cmd, mini);
	return (0);
}

void	print_path_pid(t_list *cmds, int pid)
{
		t_list *current;
	t_cmd *cmd;

	current = cmds;
	while (current)
	{
		cmd = (t_cmd *)(current->content);
		if (cmd->pid == pid)
			printf("COMMAND: %s\n", cmd->path);
		current = current->next;
	}
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
		ret = execute_command(current->content, mini);
		if (cmd->in_fd)
		{
			close(cmd->out_fd);
			close(cmd->in_fd);
		}
		if (ret < 0)
			return (ret);
		current = current->next;
		amount++;
	}
	while (amount)
	{
		ret = wait(&status);
		print_path_pid(mini->cmds, ret);
		amount--;
	}
	if (((status) & 0x7f) == 0)
		mini->status = ((status) & 0xff00) >> 8;
	return (0);
}
