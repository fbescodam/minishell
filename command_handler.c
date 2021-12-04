#include "libft/libft.h"
#include "tokens.h"
#include "utils.h"
#include <stdio.h>
#include <fcntl.h>

int	file_exists(char *name)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		perror("minishell");
		return (0);
	}
	close(fd);
	return (1);
}

int	cmd_redirection(t_cmd **cmd, t_list **current_token)
{
	t_token *token;
	t_token *file_name;

	token = (t_token *)((*current_token)->content);
	file_name = (t_token *)((*current_token)->next)->content;
	if (!file_name || file_name->flag != WORD)
		return (-1);
	if (token->flag == OUTPUT_REDIR)
	{
		(*cmd)->out_file = file_name->word;
		(*cmd)->mode = (*cmd)->mode | OUT_FILE;
	}
	else if (token->flag == INPUT_REDIR)
	{
		if (!file_exists(file_name->word))
			return (0);
		(*cmd)->in_file = file_name->word;
		(*cmd)->mode = (*cmd)->mode | IN_FILE;
	}
	*current_token = (*current_token)->next;
	*current_token = (*current_token)->next;
	return (1);
}

int		add_arguments(t_cmd **cmd, t_list **current_token)
{
	int	argc;
	t_token	*token;
	t_list	*iter;
	int	i;

	argc = 0;
	iter = *current_token;
	token = (t_token *)(iter->content);
	while (iter && token->flag == WORD)
	{
		argc++;
		iter = iter->next;
		if (iter)
			token = (t_token *)(iter->content);
	}
	(*cmd)->params = (char **)malloc(sizeof(char *) * (argc + 1));
	if (!((*cmd)->params))
		return (-1);
	((*cmd)->params)[argc] = 0;
	i = 0;
	while (i < argc)
	{
		token = (t_token *)((*current_token)->content);
		((*cmd)->params)[i] = token->word;
		(*current_token) = (*current_token)->next;
		i++;
	}
	return (1);
}

int	setup_cmd(t_cmd **cmd, t_list *tokens)
{
	t_list *current_token;
	t_token *token;
	int	ret;

	(*cmd)->mode = 0;
	current_token = tokens;
	while (current_token)
	{
		token = (t_token *)(current_token->content);
		if (token->flag == OUTPUT_REDIR || token->flag == INPUT_REDIR)
			ret = cmd_redirection(cmd, &current_token);
		if (ret <= 0)
			return (ret); //parse error or file not found
		if (token->flag == WORD)
			ret = add_arguments(cmd, &current_token);
		if (ret == -1)
			return (-1); // malloc error
	}
	return (1);
}
