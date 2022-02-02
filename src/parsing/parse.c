#include "structs.h"
#include "custom_errors.h"
#include "debug.h"
#include "error_handling.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "parse.h"

// scan for ; and "
// if " is found, check if it closes, if not parse error
// if it closes add split until operator, but also add quoted text all in one string

// this will not work now though because there is no difference in my parsing between "     " cat    and "     " | cat
// "         " cat should stick together, "      " | cat should be two strings. Skip the characters within quotes
// the parse_cmd stage will then separate them in different arguments

int	double_quote_check(char *prompt, int first_quote_index)
{
	int		close_index;
	char	quote[2];

	quote[0] = prompt[first_quote_index];
	quote[1] = '\0';
	prompt += (first_quote_index + 1);
	close_index = scan_operators(prompt, quote, 0);
	if (prompt[close_index] == '\0')
		return (-1);
	return (close_index + 1);
}

int	quote_search_index(char *prompt)
{
	int	nxt_quote;
	int	end_quote_index;
	int	ret;

	nxt_quote = 0;
	end_quote_index = 0;
	ret = 0;
	while(1)
	{
		nxt_quote = scan_operators(prompt + ret, "\'\"|", 0);
		if (prompt[nxt_quote + ret] == '\0' || prompt[nxt_quote + ret] == '|')
			return (ret);
		ret += nxt_quote;
		end_quote_index = double_quote_check(prompt, ret);
		if (end_quote_index < 0)
			return (-1);
		ret += end_quote_index;
		ret++;
	}
}

int	next_operator_index(char *prompt, char *set)
{
	int		next_operator;
	int		end_quote_index;

	end_quote_index = 0;
	next_operator = 0;
	next_operator = skip_chars(prompt, " ") - prompt;
	if (prompt[next_operator] == '\0')
		return (0);
	if (prompt[next_operator] == *set)
		return (-1);
	next_operator = quote_search_index(prompt);
	if (next_operator < 0)
		return (-1);
	next_operator += scan_operators(prompt + next_operator, set, 0);
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
		ret = setup_cmds(mini, prompt_split);
		if (ret == -1)
			return (ENOMEM);
		if (ret == -2)
			return (PARSE_ERROR);
		//ret = setup_cmds(mini, prompt_split);
	}
	return (0);
}
