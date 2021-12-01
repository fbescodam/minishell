#include "libft/libft.h"
#include "tokens.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int		add_operator_token(char *prompt, t_list **tokens, int *i)
{
	int	ret;
	if (prompt[0] == '\0')
		return (0);
	if (prompt[0] == '<' && prompt[1] == '<')
	{
		ret = setup_operator_token(tokens, INPUT_REDIR_APPEND);
		*i = *i + 1;
	}
	else if (prompt[0] == '>' && prompt[1] == '>')
	{
		ret = setup_operator_token(tokens, OUTPUT_REDIR_APPEND);
		*i = *i + 1;
	}
	else if (prompt[0] == '<')
		ret = setup_operator_token(tokens, INPUT_REDIR);
	else if (prompt[0] == '>')
		ret = setup_operator_token(tokens, OUTPUT_REDIR);
	else
		ret = setup_operator_token(tokens, PIPE);
	return (ret);
}

int		add_word_tokens(char *words, t_list **tokens)
{
	char **words_list;
	t_token	*new;
	t_list	*new_instance;
	int ret;

	words_list = ft_split(words, ' ');
	if (!words_list)
		return(-1);
	if ( words_list[0] == 0 || words_list[0][0] == '\0' )
	{
		//free word_list
		return (0);
	}
	ret = setup_word_token(tokens, words_list);
	if (ret == -1)
		return (-1);
	return (1);
}

int		scan_operators(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '<' || prompt[i] == '|' || prompt[i] == '>')
		{
			return (i);
		}
		i++;
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
		if (token->flag == WORD)
		{
			printf("THIS TOKEN IS  WORD-TYPE\n");
			int i = 0;
			while (token->words[i])
			{
				printf("SPLIT WORDS IN TOKEN : '%s'\n", token->words[i]);
				i++;
			}
		}
		else if (token->flag == INPUT_REDIR)
			printf("THIS TOKEN IS INPUT_REDIR\n");
		else if (token->flag == OUTPUT_REDIR)
			printf("THIS TOKEN IS OUTPUT_REDIR\n");
		else if (token->flag == INPUT_REDIR_APPEND)
			printf("THIS TOKEN IS INPUT_REDIR_APPEND\n");
		else if (token->flag == OUTPUT_REDIR_APPEND)
			printf("THIS TOKEN IS OUTPUT_REDIR_APPEND\n");
		else if (token->flag == PIPE)
			printf("THIS TOKEN IS PIPE\n");
		else
			printf("TOKEN UNKNOWN, %d\n", token->flag);
		current_token = current_token->next;
	}
}

int		tokenize(char *prompt)
{
	int	next_operator;
	char *cmd;
	int	i;
	t_list *tokens;
	int ret;

	i = 0;
	tokens = 0;
	while (prompt[i])
	{
		next_operator = scan_operators(prompt + i);
		cmd = ft_substr(prompt + i, 0, next_operator);
		if (!cmd)
			return (-1); //proper error hanling goes here
		if (cmd[0] != '\0')
			ret = add_word_tokens(cmd, &tokens);
		if (ret == -1)
			return (-1); //proper error handling goes here
		ret = add_operator_token(prompt + i + next_operator, &tokens, &i);
		if (ret == -1)
			return (-1); //proper error handling goes here
		free(cmd);
		i += next_operator + 1;
	}
	print_token_list(tokens);
	return (1);

}
