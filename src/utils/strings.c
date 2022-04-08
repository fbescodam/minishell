/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strings.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 17:21:57 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/08 22:43:40 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
	#include <stdio.h>

/**
 * @brief Get the next single quote in a string, skipping over double quotes
 *
 * @param[in] str The string to search in
 * @return A pointer to the next single quote in the string
 */
char	*get_next_single_quote(char *str)
{
	char	is_in_dquotes;
	char	*temp;

	is_in_dquotes = 0;
	temp = str;
	while (*temp)
	{
		if (*temp == '"')
			is_in_dquotes = !is_in_dquotes;
		else if (!is_in_dquotes && *temp == '\'')
			return (temp);
		temp++;
	}
	return (NULL);
}

/**
 * @brief Skip over single quotes in a string
 *
 * @param[in] str The string, starting at the first ' character
 * @return Returns 0 if no single quotes found in string
 */
int skip_over_single_quotes(char **str)
{
	char	*temp;

	temp = get_next_single_quote(*str + 1);
	if (!temp)
		return (0);
	*str = temp;
	return (1);
}

/**
 * @brief Remove all occurrances of a certain character from a string
 *
 * @param[in] str The string to remove the characters from (allocated by malloc)
 * @param[in] rem The character to remove
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

/**
 * @brief Replace spaces with the NULL character if they're not in between
 * apostrophes. To be used with ft_strmapi.
 *
 * @param[in] pos The position of the character in the string
 * @param[in] c The character in the string
 * @return The character to replace the current position with
 */
char	replace_space_with_null(unsigned int pos, char c)
{
	static char		in_quotes;
	static char		last_quote;

	if (pos == 0)
		in_quotes = 0;
	if (!in_quotes && (c == '\"' || c == '\''))
	{
		in_quotes = 1;
		last_quote = c;
	}
	else if (in_quotes && c == last_quote)
		in_quotes = 0;
	else if (!in_quotes && c == ' ')
		return ('\0');
	return (c);
}
