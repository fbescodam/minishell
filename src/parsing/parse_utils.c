#include "custom_errors.h"
#include "libft.h"
#include <stdlib.h>
#include "utils.h"

int	is_fd_redir(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i] <= '9' && prompt[i] >= '0')
		i++;
	if (i == 0)
		return (0);
	if (prompt[i] == '>' || prompt[i] == '<')
		return (1);
	return (0);
}

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

int		scan_operators(char *prompt, char *operators, int quote_is_operator)
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
			if ((prompt[i] == '\"' || prompt[i] == '\'') && quote_is_operator)
				return (i);
			k++;
		}
		i++;
		k = 0;
	}
	return (i);
}

/**
 * @brief skips characters in the set
 * @param[in] prompt, set of characters
 * @return pointer to the next character in the string after skipping
 */

char	*skip_chars(char *prompt, char *mask_set)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (prompt[i])
	{
		while (mask_set[k])
		{
			if (prompt[i] == mask_set[k])
				k++;
			else
				return (prompt + i);
		}
		i++;
		k = 0;
	}
	return (prompt + i);

}

/**
 * @brief a strjoin that reallocates the string
 * @param[in] destination string, source string, length to append
 * @return 0 on default, -1 in case of failed allocation
 */

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
