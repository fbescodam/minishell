#include "structs.h"
#include "debug.h"
#include "utils.h"
#include "custom_errors.h"
#include <stdlib.h>
#include "parse.h"
#include <stdio.h>

int	add_quoted_strings(char *prompt, char ***dest)
{
	int	nxt_quote;
	int	end_quote_index;
	int	ret;
	int	err;

	nxt_quote = 0;
	end_quote_index = 0;
	ret = 0;
	while(1)
	{
		nxt_quote = scan_operators(prompt + ret, "\'\"><", 0);
		if (prompt[nxt_quote + ret] != '\"' && prompt[nxt_quote + ret] != '\'')
			return (ret);
		ret += nxt_quote;
		end_quote_index = double_quote_check(prompt, ret);
		if (end_quote_index < 0)
			return (-2);
		err = split_and_add(prompt + ret + 1, dest, end_quote_index - 1);
		if (err != 0)
			return (-1);
		ret += end_quote_index;
		ret++;
	}
}

int	join_realloc(char **dest, char *src, char len)
{
	char	*temp;
	char	*split;

	split = ft_substr(src, 0, len);
	if (!split)
		return (-1);
	temp = ft_strjoin(*dest, split);
	free(split);
	if (!temp)
		return (-1);
	free(*dest);
	*dest = temp;
	return (0);
}

int	add_param(char **param_buffer, char ***dest)
{
	char	*param;
	int		err;

	param = ft_strdup(*param_buffer);
	if (!param)
		return (-1);
	err = add_string_to_array(dest, param);
	free(*param_buffer);
	if (err != 0)
		return (-1);
	*param_buffer = ft_strdup("");
	if (!*param_buffer)
		return (-1);
	return (0);
}

int	close_param(char **buff, char **prompt, int len, char ***dest)
{
	int	err;

	printf("PROMPT IN CLOsE PARAM:%s\n", *prompt);
	printf("LEN:%d\n", len);
	err = join_realloc(buff, *prompt, len);
	if (err != 0)
		return (-1);
	err = add_param(buff, dest);
	if (err != 0)
		return (-1);
	*prompt += len;
	printf("PROMPT AFTER ADD : %s\n", *prompt);
	while (**prompt == ' ')
		(*prompt)++;
	printf("GODDAMN\n");
	return (0);
}

int	handle_quotes(char **buff, char **prompt, int quote_pos)
{
	char	*quoted_string;
	int		err;
	int		str_len;

	printf("QUOTEPOS : %s:\n", *prompt + quote_pos);
	err = get_quoted_string(*prompt + quote_pos, &quoted_string);
	printf("QUOTEDSTRING: %s:\n", quoted_string);
	printf("STRLEN: %d\n", str_len);
	if (err < 0)
		return (-1);
	printf("GOTHERE\n");
	str_len = ft_strlen(quoted_string);
	err = join_realloc(buff, quoted_string, str_len -2);
	free(quoted_string);
	if (err != 0)
		return (-1);
	*prompt += str_len + quote_pos + 2;
	return (0);
}

int	parse_params(char *prompt, char ***dest)
{
	char	*prompt_start;
	char	*buff;
	int		nxt_delim;
	int		nxt_quote;
	int		err;

	prompt_start = prompt;
	buff = ft_strdup("");
	if (!buff)
		return (-1);
	err = 0;
	while (1)
	{
		printf("PROMPT:%s:", prompt);
		if (*prompt == '\0')
			break;
		nxt_delim = scan_operators(prompt, " <>", 0);
		nxt_quote = scan_operators(prompt, "\'\"", 0);
		if (nxt_delim <= nxt_quote)
			err = close_param(&buff, &prompt, nxt_delim, dest);
		else
			err = handle_quotes(&buff, &prompt, nxt_quote);
		if (*prompt == '<' || *prompt == '>')
			break;
		if (err != 0)
			return (-1);
	}
	printf("prompt - start:%ld\n", prompt - prompt_start);
	return(prompt - prompt_start);
}

int	parse_operator(char *prompt, int index, t_cmd *cmd)
{
	int	ret;

	if (prompt[index] == '<')
		ret = parse_input_redir(prompt + index, cmd);
	//else if (prompt[index] == '<')
	//	ret = parse_input_redir(prompt + index, cmd);åå
	//else if (prompt[index] == '\'' || prompt[index] == '\"') 
	//	ret = add_quoted_strings(prompt + index, &(cmd->params));

	return(ret);
}

int	parse_cmd(t_list *cmd, char *prompt)
{
	int	ret;
	int	index;
	t_cmd	*current_cmd;

	ret = 0;
	index = 0;
	current_cmd = (t_cmd *)(cmd->content);
	current_cmd->params = ft_calloc(1, sizeof(char *));
	if (!(current_cmd->params))
		return (ENOMEM);
	while (prompt[index])
	{
		ret = parse_params(prompt, &(current_cmd->params));
		if (ret < 0)
			return (ret);
		index += ret;
		if (!prompt[index])
			break;
		ret = parse_operator(prompt, index, current_cmd);
		if (ret < 0)
			return (ret); // ENOMEM OR PARSE ERROR
		index += ret;
	}
	print_char_array(current_cmd->params);
	return (0);
}

t_list	*new_cmd(t_mini *mini)
{
	t_cmd	*cmd;
	t_list	*cmd_instance;

	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->mini = mini;
	cmd_instance = ft_lstnew(cmd);
	if (!cmd_instance)
	{
		free(cmd);
		return(NULL);
	}
	if (!(mini->cmds))
		mini->cmds = cmd_instance;
	else
		ft_lstadd_back(&(mini->cmds), cmd_instance);
	return (cmd_instance);
}

int	setup_cmds(t_mini *mini, char **prompts)
{
	int	i;
	t_list	*current_cmd;
	i = 0;
	int ret;

	ret = 0;
	while (prompts[i])
	{
		current_cmd = new_cmd(mini);
		if (current_cmd == NULL)
				return(ENOMEM);
		//if (i > 0)
		//	pipe_in(current_cmd->content, &fd);
		ret = parse_cmd(current_cmd, prompts[i]);
		if (ret != 0)
			return (ret);
		//if (commands[i + 1])
		//	pipe_out(current_cmd->content, &fd);
		i++;
	}
	return (ret);
}
