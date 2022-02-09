#include "structs.h"
#include "debug.h"
#include "execute.h"

int		execute_command(t_cmd *cmd, t_mini *mini)
{
	int		ret;
	int		pid;
	int		status;
	int		terminated_process;

	terminated_process = 0;
	ret = check_command(cmd, mini);
	print_command_status(cmd, ret);
	return (0);
	/* pid = fork();
	if (pid == -1)
		exit_shell_w_error(cmd, 0);
	signal(SIGINT, handler);
	if (pid == 0)
		child_process(cmd);
	while (terminated_process != pid)
		terminated_process = wait(&status);
	if (cmd->out_fd)
		close(cmd->out_fd);
	if (((status) & 0x7f) == 0)
		errno = ((status) & 0xff00) >> 8;
	if (errno != RESERVED)
		return ;
	ret = check_run_reserved_cmds(cmd);
	if (ret > 0)
		perror("minishell"); */
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
