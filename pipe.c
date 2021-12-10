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

int		pipe_out(t_list **tokens, int *fd)
{
	t_cmd *cmd;
	t_token *out_token;
	t_list *new;

	cmd = (t_cmd *)malloc (sizeof(t_cmd));
	if (!cmd)
		return (ENOMEM);
	cmd->tokens = *tokens;
	out_token = pipe_token(fd, PIPE_OUT);
	if (!out_token)
		return (ENOMEM);
	new = ft_lstnew(out_token);
	if (!new)
		return (ENOMEM);
	ft_lstadd_back(tokens, new);
	execute_command(cmd, set_path());
	//free cmd and its contents
	close(fd[1]);
	return (0);
}

int		setup_pipe(t_list **tokens)
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
	in_token = pipe_token(fd, PIPE_IN);
	if (!in_token)
		return (ENOMEM);
	new = ft_lstnew(in_token);
	if (!new)
		return (ENOMEM);
	*tokens = ft_lstnew(in_token);
	return (0);
}
