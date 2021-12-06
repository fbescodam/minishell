#include "libft/libft.h"
#include "tokens.h"
#include "utils.h"
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include "custom_errors.h"

int	setup_cmd(t_cmd *cmd)
{
	t_list *current_token;
	t_token *token;
	int	ret;

	cmd->mode = 0;
	current_token = cmd->tokens;
	cmd->argc = 0;
	ret = 0;
	while (current_token)
	{
		token = (t_token *)(current_token->content);
		if (token->flag == OUTPUT_REDIR || token->flag == INPUT_REDIR)
			ret = cmd_redirection(cmd, &current_token);
		else if (token->flag == WORD)
			ret = add_arguments(&cmd, token);
		if (ret == -1)
			return (errno);
		current_token = current_token->next;
	}
	return (ret);
}

void	handler()
{
	printf("\n");
}

void	child_process(t_cmd *cmd)
{
	int	ret;

	signal(SIGINT, SIG_DFL);
	ret = setup_cmd(cmd);
	if (ret != 0)
		exit_shell_w_error(ret);
	if (!cmd->params)				// no cmd tokens found
		exit(errno);
	if (is_reserved(cmd))
		exit (RESERVED);
	execv(cmd->path, cmd->params);	// if not a reserved command, run it with execv
	if (!cmd->path)
		exit_shell_w_error(127);
	exit_shell_w_error(0);
}

void	execute_command(t_cmd *cmd, char **paths)
{
	int		ret;
	int		pid;
	int		status;
	int		terminated_process;
	
	terminated_process = 0;
	cmd->path = check_command(cmd, paths);
	pid = fork();
	if (pid == -1)
		exit_shell_w_error(0);
	signal(SIGINT, handler);
	if (pid == 0)
		child_process(cmd);
	while (terminated_process != pid)
		terminated_process = wait(&status);
	if (((status) & 0x7f) == 0)
		errno = ((status) & 0xff00) >> 8;
	if (errno != RESERVED)
		return ;
	ret = check_run_reserved_cmds(cmd);
	if (ret < 0)
		perror("minishell");
}	
