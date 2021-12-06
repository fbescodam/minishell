#include "utils.h"
#include <stdlib.h>
#include "tokens.h"

int		char_array_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	append_char_array(char **from, char **to)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (to[i])
		i++;
	while (from[j])
	{
		to[i + j] = from[j];
		j++;
	}
	to[i + j] = 0;
}


int		add_arguments(t_cmd **cmd, t_token	*token)
{
	char	**temp;
	int		token_size;

	if ((*cmd)->argc == 0)
	{
		(*cmd)->params = token->content;
		(*cmd)->argc = char_array_len((*cmd)->params);
		return (0);
	}
	token_size = char_array_len((char **)(token->content));
	temp = (char **)malloc(sizeof(char *) * (*cmd)->argc + token_size + 1);
	if (!temp)
		return (-1);
	temp[0] = 0;
	append_char_array((*cmd)->params, temp);
	free((*cmd)->params);
	append_char_array((char **)(token->content), temp);
	(*cmd)->argc += token_size;
	(*cmd)->params = temp;
	return (0);
}
