#include "structs.h"
#include <stdlib.h>
//#include "tokens.h"
#include <errno.h>
#include <stdio.h>

/*
 * @brief Counts and returns how many strings in an array of type char **
 */

size_t	char_array_len(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	*get_last_from_char_array(char **arr)
{
	char	**temp;

	temp = arr;
	while (*temp)
		temp++;
	return (*temp);
}

int	add_string_to_array(char ***to, char *from)
{
	size_t	arr_size;
	char	**temp;
	int		i;

	if (!from)
		return (-1);
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
