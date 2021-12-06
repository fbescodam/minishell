#include "libft/libft.h"
#include "tokens.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "utils.h"
#include "custom_errors.h"

int		setup_pipe(t_list **tokens)
{
	t_cmd *cmd;
	t_list *new;
	t_token *in_token;
	t_token *out_token;
	int	*fd;

	
	cmd = (t_cmd *)malloc (sizeof(t_cmd));
	fd = (int *)malloc (sizeof(int) * 2);
	if (!cmd | !fd)
		return (ENOMEM);
	pipe(fd);
	if (!(*tokens))
		return (PARSE_ERROR);
	cmd->tokens = *tokens;
	
	out_token = (t_token *)malloc(sizeof(t_token));
	
	if (!out_token)
		return (ENOMEM);
	out_token->content = fd;
	out_token->flag = PIPE_OUT;
	new = ft_lstnew(in_token);
	if (!new)
		return (ENOMEM);
	ft_lstadd_back(tokens, new);
	in_token = (t_token *)malloc(sizeof(t_token));
	if (!in_token)
		return (ENOMEM);
	in_token->content = fd;
	in_token->flag = PIPE_IN;
	execute_command(cmd, set_path());
	// free  cmd
	close(fd[1]);
	*tokens = ft_lstnew(in_token);
	return (0);
}
