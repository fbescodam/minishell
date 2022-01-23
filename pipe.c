#include "libft/libft.h"
#include "tokens.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "utils.h"
#include "custom_errors.h"

t_token		*pipe_token(int *fd, int flag)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (0);
	token->content = fd;
	token->flag = flag;
	return (token);
}

int		pipe_out(t_cmd *cmd, int **fd)
{
	t_token *out_token;
	t_list *new;
	int		ret;

	*fd = (int *)malloc (sizeof(int) * 2);
	if (!fd)
		return (ENOMEM);
	ret = pipe(*fd);
	cmd->out_fd = (*fd)[1];
	if (ret < 0)
		return (errno);
	out_token = pipe_token(*fd, PIPE_OUT);
	if (!out_token)
		return (ENOMEM);
	new = ft_lstnew(out_token);
	if (!new)
		return (ENOMEM);
	ft_lstadd_back(&(cmd->tokens), new);
	return (0);
}

int	pipe_in(t_cmd *cmd, int **fd)
{
	t_token	*in_token;

	in_token = pipe_token(*fd, PIPE_IN);
	if (!in_token)
		return (ENOMEM);
	cmd->tokens = ft_lstnew(in_token);
	if (!(cmd->tokens))
		return(ENOMEM);
	return(0);
}

/* int		setup_pipe(t_list **tokens, t_list **cmds)
{
	t_list *new;
	t_token *in_token;
	int	*fd;
	int	ret;

	if (!(*tokens))
		return (PARSE_ERROR);
	fd = (int *)malloc (sizeof(int) * 2);
	if (!fd)
		return (ENOMEM);
	ret = pipe(fd);
	if (ret < 0)
		return (errno);
	ret = pipe_out(tokens, fd);
	if (ret != 0)
		return (ret);
	ret = pipe_in(fd, cmds);
	
	return (ret);
} */
