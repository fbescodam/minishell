#include "../include/structs.h"
#include <stdlib.h>
//#include "tokens.h"
#include <errno.h>
#include <stdio.h>

/*
 * @brief Counts and returns how many strings in an array of type char **
 */

int		char_array_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	add_string_to_array(char ***to, char *from)
{
	int		arr_size;
	char	**temp;
	int		i;

	i = 0;
	arr_size = char_array_len(*to);
	temp = ft_calloc(arr_size + 2, sizeof(char *));
	if (!temp)
		return (ENOMEM);
	while((*to)[i])
	{
		temp[i] = (*to)[i];
		i++;	
	}
	ft_free(*to);
	temp[i] = from;
	temp[i + 1] = 0;
	*to = temp;
	return (0);
}


/*
 * @brief Appends strings **from array **to array
 */

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

/*
 * @brief Re-allocates the params array of cmd to fit more arguments
 * : this is needed when argument tokens are broken up by other types
 * for example : ' cat main.c > output setup.c '
 * @return : 0 on success, -1 on malloc error
 */

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
	temp = (char **)ft_calloc((*cmd)->argc + token_size + 1, sizeof(char *));
	if (!temp)
		return (-1);
	temp[0] = 0;
	append_char_array((*cmd)->params, temp);
	ft_free_double_ptr((void **)(*cmd)->params);
	append_char_array((char **)(token->content), temp);
	(*cmd)->argc += token_size;
	(*cmd)->params = temp;
	return (0);
}
