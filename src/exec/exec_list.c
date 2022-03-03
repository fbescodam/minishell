#include "structs.h"
#include "debug.h"
#include "execute.h"
#include "envars.h"
#include "error_handling.h"
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

void	handler()
{
	printf("\n");
}

void	write_heredoc(t_cmd *cmd, t_mini *mini)
{
	int	fd[2];
	int	ret;
	int	pid;
	int status;

	if (cmd->pipe_in[0])
	{
		close(cmd->pipe_in[0]);
		close(cmd->pipe_in[1]);
	}
	ret = pipe(fd);
	if (ret < 0)
		force_exit(mini, errno);
	cmd->pipe_in[0] = fd[0];
	cmd->pipe_in[1] = fd[1];
	pid = fork();
	if (pid == -1)
		force_exit(mini, errno);
	if (pid == 0)
	{
		close(fd[0]);
		ret = dup2(fd[1], 1);
		if (ret < 0)
			exit(errno);
		close(fd[1]);
		ret = ft_putstr_fd(cmd->heredoc, 1);
		if (ret < 0)
			exit(errno);
		exit (0);
	}
	wait_n_processes(1, mini);

}

void	fork_process(t_cmd *cmd, t_mini *mini)
{
	int		pid;

	if (cmd->heredoc != NULL)
		write_heredoc(cmd, mini);
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

void	wait_n_processes(int amount, t_mini *mini)
{
	int	ret;
	int	status;

	while (amount)
	{
		ret = wait(&status);
		if (ret == -1)
			perror("minishell");
		amount--;
	}
	if (((status) & 0x7f) == 0)
		set_mini_status(mini, ((status) & 0xff00) >> 8);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGSEGV)
			error_manager(mini, SEGF);
	}
}

int		execute_list(t_mini *mini)
{
	t_list	*current;
	int		ret;
	t_cmd	*cmd;
	int		amount;

	amount = 0;
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
	wait_n_processes(amount, mini);
	return (0);
}
