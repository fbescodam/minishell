#include "structs.h"
#include "debug.h"
#include "utils.h"
#include "custom_errors.h"
#include <stdlib.h>
#include <stdio.h>
#include "parse.h"

int	parse_file_name(char *prompt, char ***dest)
{
	char	*prompt_start;
	char	*buff;
	int		ret;

	prompt_start = prompt;
	buff = ft_strdup("");
	if (!buff)
		return (-1);
	ret = 0;
	while (ret == 0 && !(**dest))
	{
		ret = search_params(&buff, &prompt, dest);
		if (ret == -1)
			return (-1);
	}
	if (*buff)
		ret = add_param(&buff, dest);
	if (ret < 0)
		return (-1);
	free(buff);
	return(prompt - prompt_start);
}

int	redir_type_check(char *prompt)
{
	char	*redir;
	char	*next_char;
	
	while (ft_isdigit(*prompt))
		prompt++;
	if (prompt[0] == prompt[1])
	{
		next_char = prompt + 2;
		while (*next_char == ' ')
			next_char++;
		if (*next_char == '<' || *next_char == '>' || *next_char == '\0')
			return (-1);
		if (prompt[0] == '<')
			return (HEREDOC);
		return (OUT_FILE_APPEND);
	}
	next_char = prompt + 1;
	while (*next_char == ' ')
			next_char++;
	if (*next_char == '<' || *next_char == '>' || *next_char == '\0')
			return (-1);
	if (prompt[0] == '<')
		return (IN_FILE);
	return (OUT_FILE);
}

int	add_token(void *content, int flag, t_cmd *cmd, char *prompt)
{
	t_token	*token;
	t_list	*new;

	token = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (-1);
	token->content = content;
	token->flag = flag;
	if (flag == HEREDOC)
		flag = read_heredoc(cmd, (char *)content);
	if (flag < 0)
		return (-1);
	token->fd = -1;
	if (ft_isdigit(*prompt))
		token->fd = ft_atoi(prompt);
	new = ft_lstnew(token);
	if (!new)
		return (-1);
	if (cmd->tokens == 0)
		cmd->tokens = new;
	else
		ft_lstadd_back(&(cmd->tokens), new);
	return (0);
}

int	parse_input_redir(char *prompt, t_cmd *cmd)
{
	char	**dest;
	int		ret;
	int		flag;
	int		size;

	flag = redir_type_check(prompt);
	if (flag < 0)
		return (-2);
	dest = ft_calloc(1, sizeof(char*));
	if (!dest)
		return (-1);
	size = 1;
	while (ft_isdigit(*(prompt + size - 1)))
		size++;
	if (flag > 2)
		size++;
	ret = parse_file_name(prompt + size, &dest);
	if (ret < 0)
		return (ret);
	size += ret;
	ret = add_token(*dest, flag, cmd, prompt);
	free(dest);
	if (ret < 0)
		return (-1);
	return (size);
}
