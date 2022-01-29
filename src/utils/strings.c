#include <stdlib.h>
#include "libft.h"

/**
 * @brief Skip over single quotes in a string
 *
 * @param str The string
 * @return Returns 0 if no single quotes found in string
 */
int skip_over_single_quotes(char **str)
{
	char	*temp;

	temp = ft_strchr(*str + 1, '\'');
	if (!temp)
		return (0);
	*str = temp;
	return (1);
}

/**
 * @brief Remove all occurrances of a certain character from a string
 *
 * @param str The string to remove the characters from (allocated by malloc)
 * @param rem The character to remove
 * @return Returns 1 if the contents of the string were modified
 */
int	remove_character(char **str, char rem)
{
	int		any_change;
	char	*found;

	any_change = 0;
	found = ft_strchr(*str, rem);
	while (found)
	{
		any_change = 1;
		ft_memmove(found, found + 1, ft_strlen(found));
		found = ft_strchr(found, rem);
	}
	if (any_change)
	{
		found = ft_strdup(*str);
		if (found)
		{
			free(*str);
			*str = found;
		}
	}
	return (any_change);
}
