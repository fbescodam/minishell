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
	while (terminated_process != pid)
		terminated_process = wait(&status);
	if (cmd->out_fd)
		close(cmd->out_fd);
	if (((status) & 0x7f) == 0)
		mini->status = ((status) & 0xff00) >> 8;
	return ;
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

int		execute_list(t_mini *mini)
{
	t_list	*current;
	int		ret;

	current = mini->cmds;
	while (current)
	{
		ret = execute_command(current->content, mini);
		if (ret < 0)
			return (ret);
		current = current->next;
	}
	return (0);
}
