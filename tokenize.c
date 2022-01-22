#include "libft/libft.h"
#include "tokens.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "utils.h"

int		add_operator_token(char *prompt, t_list **tokens, int *i)
{
	int	ret;

	if (prompt[0] == '\0')
		return (0);
	if (prompt[0] == '<' && prompt[1] == '<')
	{
		ret = setup_operator_token(tokens, INPUT_REDIR_APPEND, prompt + 1, i);
		*i = *i + 1;
	}
	else if (prompt[0] == '>' && prompt[1] == '>')
	{
		ret = setup_operator_token(tokens, OUTPUT_REDIR_APPEND, prompt + 1, i);
		*i = *i + 1;
	}
	else if (prompt[0] == '<')
		ret = setup_operator_token(tokens, INPUT_REDIR, prompt, i);
	else if (prompt[0] == '>')
		ret = setup_operator_token(tokens, OUTPUT_REDIR, prompt, i);
	else
		ret = setup_pipe(tokens);
	return (ret);
}

int		add_word_tokens(char *words, t_list **tokens)
{
	char	**words_list;
	int		ret;

	words_list = ft_split(words, ' ');
	if (!words_list)
		return (ENOMEM);
	if (!(words_list[0])) //can this also happen in split ?  || words_list[0][0] == '\0' 
	{
		free(words_list);
		return (0);
	}
	ret = setup_word_token(tokens, words_list);
	return (ret);
}

int		scan_operators(char *prompt, char *operators)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (prompt[i])
	{
		while (operators[k])
		{
			if (prompt[i] == operators[k])
				return (i);
			k++;
		}
		i++;
		k = 0;
	}
	return (i);
}

void	print_token_list(t_list *tokens)
{
	t_list *current_token;
	t_token *token;

	current_token = tokens;
	while (current_token)
	{
		token = (t_token *)(current_token->content);
		if (token->flag == CMD)
		{
			printf("THIS TOKEN IS  CMD-TYPE :\n");
			int i = 0;
			char **params = (char **)(token->content);
			while (params[i])
			{
				printf("'%s', ", params[i]);
				i++;
			}
			printf("\n");
		}
		else if (token->flag == INPUT_REDIR)
			printf("THIS TOKEN IS INPUT_REDIR\n");
		else if (token->flag == OUTPUT_REDIR)
			printf("THIS TOKEN IS OUTPUT_REDIR\n");
		else if (token->flag == INPUT_REDIR_APPEND)
			printf("THIS TOKEN IS INPUT_REDIR_APPEND\n");
		else if (token->flag == OUTPUT_REDIR_APPEND)
			printf("THIS TOKEN IS OUTPUT_REDIR_APPEND\n");
		else if (token->flag == PIPE_IN || token->flag == PIPE_OUT)
			printf("THIS TOKEN IS PIPE\n");
		else
			printf("TOKEN UNKNOWN, %d\n", token->flag);
		current_token = current_token->next;
	}
}

int		tokenize(char *prompt, t_list **cmds)
{
	int	next_operator;
	char *cmd;
	int	i;
	int ret;
	t_list *tokens;

	i = 0;
	tokens = 0;
	ret = 0;
	while (prompt[i])
	{
		next_operator = scan_operators(prompt + i, "<>");
		cmd = ft_substr(prompt + i, 0, next_operator);
		if (!cmd)
			return (ENOMEM);
		if (cmd[0] != '\0')
			ret = add_word_tokens(cmd, &tokens);
		free(cmd);
		if (ret != 0)
			return (ret);
		ret = add_operator_token(prompt + i + next_operator, &tokens, &i);
		if (ret != 0)
			return (ret);
		i += next_operator;
		if (prompt[i] != '\0')
			i++;
	}
	((t_cmd *)((*cmds)->content))->tokens = tokens;
	print_token_list(tokens);
	return (0);

}
