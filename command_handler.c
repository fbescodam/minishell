#include "libft/libft.h"
#include "tokens.h"
#include "utils.h"
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int	cmd_redirection(t_cmd *cmd, t_list **current_token)
{
	t_token *token;
	int	ret;

	ret = 1;
	token = (t_token *)((*current_token)->content);
	if (token->flag == OUTPUT_REDIR)
	{
		cmd->out_file = token->content;
		cmd->mode = cmd->mode | OUT_FILE;
		ret = output_redirect(cmd->mode, cmd);
	}
	else if (token->flag == INPUT_REDIR)
	{
		cmd->in_file = token->content;
		cmd->mode = cmd->mode | IN_FILE;
		ret = input_redirect(cmd->mode, cmd);
	}
	return (ret);
}

int	setup_cmd(t_cmd *cmd)
{
	t_list *current_token;
	t_token *token;
	int	ret;

	cmd->mode = 0;
	current_token = cmd->tokens;
	ret = 1;
	while (current_token)
	{
		token = (t_token *)(current_token->content);
		if (token->flag == OUTPUT_REDIR || token->flag == INPUT_REDIR)
			ret = cmd_redirection(cmd, &current_token);
		if (ret <= 0)
			return (ret); //parse error or file not found
		if (token->flag == WORD) 
		{
			//check if command is exit or variable setting
			cmd->params = token->content;
		}
		current_token = current_token->next;
	}
	return (1);
}

void	handler()
{
	printf("\n");
}

void	execute_command(t_cmd *cmd, char **paths)
{
	int		ret;
	int		pid;
	int		status;
	int		terminated_process;

	terminated_process = 0;
	ret = 0;
	cmd->path = check_command(cmd->tokens, paths);
	pid = fork();
	signal(SIGINT, handler);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		ret = setup_cmd(cmd);
		if (ret == -1)
			exit_shell_w_error(0);
		execv(cmd->path, cmd->params);
		if (!cmd->path)
			exit_shell_w_error(127);
		exit_shell_w_error(0);
	}
	while (terminated_process != pid)
		terminated_process = wait(&status);
	if (((status) & 0x7f) == 0)
		errno = ((status) & 0xff00) >> 8;
}
