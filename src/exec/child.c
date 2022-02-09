#include "structs.h"
#include "execute.h"
#include <errno.h>
#include <signal.h>
#include "error_handling.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	exit_child(char *process_name)
{
	if (errno == 127)
	{
		ft_putstr_fd(process_name, 2);
		ft_putstr_fd(": Command not found\n", 2);
	}
		
	else
		perror("minishell: ");
	exit(errno);
}

int		fd_setup(t_token *token)
{
	int	ret;

	if (token->flag == OUT_FILE || token->flag == OUT_FILE_APPEND 
		|| token->flag == PIPE_OUT)
		ret = output_redirect(token);
	else
		ret = input_redirect(token);
	return (ret);
}

int		redir_setup(t_cmd *cmd)
{
	t_list	*current_token;
	int		ret;

	ret = 0;
	current_token = cmd->tokens;
	while (current_token)
	{
		ret = fd_setup(current_token->content);
		if (ret != 0)
			return (ret);
		current_token = current_token->next;
	}
	return (ret);
}

void	child_process(t_cmd *cmd)
{
	int	ret;

	signal(SIGINT, SIG_DFL);
	ret = redir_setup(cmd);
	if (ret != 0)
		exit_child("");
	if (!*(cmd->params))
		exit_child("");
	execv(cmd->path, cmd->params);
	if (!cmd->path)
		errno = 127;
	exit_child(*(cmd->params));
}
