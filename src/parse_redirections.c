#include "structs.h"
#include "debug.h"
#include "utils.h"
#include "custom_errors.h"
#include <stdlib.h>
#include <stdio.h>

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

int	get_next_word(char *prompt, char **dest)
{
	int	end;
	int	space_skip;
	char *str;

	space_skip = 0;
	while (prompt[space_skip] == ' ')
		space_skip ++;
	end = scan_operators(prompt + space_skip, " ><", 0);
	if (end == 0)
		return(-2);
	str = ft_substr(prompt, space_skip, end);
	if (!str)
		return (-1);
	*dest = str;
	return(space_skip + end);
	
}

int	parse_input_redir(char *prompt, t_cmd *cmd)
{
	int		ret;
	char	*file;
	t_token	*token;
	int		skipped_chars;
	int		flag;

	if (prompt[1] == '\0')
		return (-2);
	skipped_chars = 1;
	flag = IN_FILE;
	if(prompt[2] == '<')
	{
		skipped_chars = 2;
		if (prompt[3] == '\0')
			return (-2);
		flag = IN_FILE_DOUBLE;
	}
	ret = get_quoted_string(prompt + skipped_chars, &file);
	if (ret < 0)
		return (ret);
	if (ret == 0)
		ret = get_next_word(prompt + skipped_chars, &file);
	if (ret < 0)
		return (ret);
	ret += skipped_chars;
	token = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (-1);
	token->content = file;
	printf("INFILE:%s\n", file);
	token->flag = IN_FILE;
	return (ret);
}

