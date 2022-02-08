#include "structs.h"
#include "custom_errors.h"
#include "debug.h"
#include "error_handling.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "parse.h"

/**
 * @brief skips through quoted text and returns index
 * @param prompt
 * @return index on default, -1 in case of parse error
 */

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

/**
 * @brief skips through quoted text and returns the next delimiter index
 * @param prompt, set of delimiters
 * @return index, -1 on parse error
 */

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

/**
 * @brief splits string until index and adds split string to an array
 * @param from: string to split, split_index, to: array
 * @return 0, error code in case of error
 */
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
/**
 * @brief splits a prompt on the set character, unless it is between quotes
 * @param from: string to split, to: destination string array, set: character
 * to split on
 * @return 0 on default, error code in case of error
 */
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

/**
 * @brief initiate parsing by splitting the prompt at every pipe and
 *  setting up commands
 * @param mini struct to set up all commands, prompt to be split
 * @return 0 on default, error code in case of error
 */
int	parse_prompt(t_mini *mini, char *prompt)
{
	char	**prompt_split;
	int		ret;

	if (*prompt)
	{
		prompt_split = ft_calloc(1, sizeof(char *));
		if (!prompt_split)
			return (ENOMEM);
		ret = split_prompt(prompt, &prompt_split, "|");
		if (ret != 0)
		{
			ft_free_double_ptr((void *)prompt_split);
			return (ret);
		}
		ret = setup_cmds(mini, prompt_split);
		ft_free_double_ptr((void *)prompt_split);
		if (ret == -1)
			return (ENOMEM);
		if (ret == -2)
			return (PARSE_ERROR);	
	}
	return (0);
}
