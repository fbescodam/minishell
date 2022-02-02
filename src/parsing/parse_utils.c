#include "custom_errors.h"
#include "libft.h"
#include <stdlib.h>

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
