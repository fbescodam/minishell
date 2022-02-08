#include "structs.h"
#include "debug.h"
#include "utils.h"
#include "custom_errors.h"
#include <stdlib.h>
#include <stdio.h>
#include "parse.h"

int	get_quoted_string(char *prompt, char **dest)
{
	int	nxt_quote;
	int	end_quote_index;
	char	*str;

	nxt_quote = 0;
	end_quote_index = 0;
	nxt_quote = scan_operators(prompt, "\'\"><", 0);
	if (prompt[nxt_quote] != '\"' && prompt[nxt_quote] != '\'')
		return (0);
	end_quote_index = double_quote_check(prompt, nxt_quote);
	if (end_quote_index < 0)
		return (-2);
	str = ft_substr(prompt, 1, nxt_quote + end_quote_index -1);
	if (!str)
		return (-1);
	*dest = str;
	return(nxt_quote + end_quote_index + 1);
}

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
	
	if (prompt[0] == prompt[1])
	{
		next_char = prompt + 2;
		while (*next_char == ' ')
			next_char++;
		if (*next_char == '<' || *next_char == '>' || *next_char == '\0')
			return (-1);
		if (prompt[0] == '<')
			return (IN_FILE_APPEND);
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

int	add_token(void *content, int flag, t_list **tokens)
{
	t_token	*token;
	t_list	*new;

	token = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (-1);
	token->content = content;
	token->flag = flag;
	new = ft_lstnew(token);
	if (!new)
		return (-1);
	if (*tokens == 0)
		*tokens = new;
	else
		ft_lstadd_back(tokens, new);
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
	if (flag > 2)
		size++;
	ret = parse_file_name(prompt + size, &dest);
	if (ret < 0)
		return (ret);
	size += ret;
	ret = add_token(*dest, flag, &(cmd->tokens));
	free(dest);
	if (ret < 0)
		return (-1);
	return (size);
}
