#include "structs.h"
#include "custom_errors.h"
#include "parse.h"
#include "debug.h"
#include "error_handling.h"
#include <stdio.h>
#include <stdlib.h>

// scan for ; and "
// if " is found, check if it closes, if not parse error
// if it closes add split until operator, but also add quoted text all in one string

int	double_quote_check(char *prompt, int first_quote_index)
{
	int	close_index;

	prompt += (first_quote_index + 1);
	close_index = scan_operators(prompt, "\"", 1);
	if (prompt[close_index] == '\0')
		return (-1);
	return (first_quote_index);
}

int	next_operator_index(char *prompt, char *set)
{
	int		next_operator;

	next_operator = skip_chars(prompt, " ") - prompt;
	if (prompt[next_operator] == '\0')
		return (0);
	if (prompt[next_operator] == *set)
		return (-1);
	next_operator = scan_operators(prompt, set, 1);
	if (prompt[next_operator] == '\"' || prompt[next_operator] == '\'')
		return (double_quote_check(prompt, next_operator));
	if (prompt[next_operator] == '\0')
		return (next_operator);
	if (prompt[next_operator + 1] == *set)
		return (-1);
	return(next_operator);
}

//function that splits string until index, adds split string to an array
int		split_and_add(char *from, char ***to, int split_index)
{
	char	*split;
	int		ret;

	split = ft_substr(from, 0, split_index);
	if (!split)
		return (ENOMEM);
	if (split[0] == '\0')
	{
		free(split);
		return (0);
	}
	ret = add_string_to_array(to, split);
	return (ret);
}

int		add_quoted_string(char *from, char ***to)
{
	int	close_index;
	int	ret;

	close_index = scan_operators(from + 1, "\"", 1);
	ret = split_and_add(from, to, close_index + 1);
	if (ret != 0)
		return (-1);
	return (close_index + 1);
}

int	split_prompt(char *from, char ***to, char *set)
{
	int		ret;
	int		nxt_op;
	char	*split;

	ret = 0;
	while (*from)
	{
		nxt_op = next_operator_index(from, set);
		if (nxt_op < 0)
			return(PARSE_ERROR);
		if (nxt_op == 0 && from[nxt_op] != '\"' && from[nxt_op] != '\'')
			return (0);
		ret = split_and_add(from, to, nxt_op);
		if (ret != 0)
			return (ret);
		from += nxt_op;
		if (*from == '\"' || *from == '\'')
			ret = add_quoted_string(from, to);
		if (ret < 0)
			return (ENOMEM);
		from += ret;
		if (*from != '\0')
			from++;
	}
	return (0);
}

int	parse_prompt(t_mini *mini, char *prompt)
{
	char	**prompt_split;
	int		ret;

	if (*prompt)
	{
		prompt_split = ft_calloc(1, sizeof(char *));
		if (!prompt_split)
			force_exit(mini, ENOMEM);
		ret = split_prompt(prompt, &prompt_split, "|");
		if (ret != 0)
			return (ret);
		print_char_array(prompt_split);
	}
	//system("leaks minishell");
	return (0);
}
