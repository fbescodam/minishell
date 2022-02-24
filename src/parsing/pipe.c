#include "structs.h"
#include <stdlib.h>
#include "custom_errors.h"
#include <stdio.h>
#include <unistd.h>

/* 
t_token		*pipe_token(int flag)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!token)
		return (0);
	token->content = NULL;
	token->flag = flag;
	return (token);
}

int		pipe_out(t_cmd *cmd)
{
	t_token *out_token;
	t_list *new;

	out_token = pipe_token(PIPE_OUT);
	if (!out_token)
		return (ENOMEM);
	new = ft_lstnew(out_token);
	if (!new)
		return (ENOMEM);
	ft_lstadd_back(&(cmd->tokens), new);
	cmd->out_fd = 1;
	return (0);
}

int	pipe_in(t_cmd *cmd)
{
	t_token	*in_token;

	in_token = pipe_token(PIPE_IN);
	if (!in_token)
		return (ENOMEM);
	cmd->tokens = ft_lstnew(in_token);
	cmd->in_fd = 1;
	if (!(cmd->tokens))
		return(ENOMEM);
	return(0);
} */
