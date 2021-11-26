/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 15:41:13 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:25:42 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_getsepsamount(char const *s, char c)
{
	size_t	amount;
	size_t	i;

	amount = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (i > 0 && s[i] == c && s[i - 1] != c)
			amount++;
		else if (s[i] != c && s[i + 1] == '\0')
			amount++;
		i++;
	}
	return (amount);
}

static char	**ft_getpartsstart(char const *s, char c, size_t amount)
{
	size_t	i;
	size_t	j;
	char	**ret;

	ret = (char **)malloc((amount + 1) * sizeof(char *));
	if (ret)
	{
		i = 0;
		j = 0;
		while (s[i] != '\0')
		{
			if (i == 0 && s[i] != c)
			{
				ret[j] = (char *)&s[i];
				j++;
			}
			else if (i > 0 && s[i] != c && s[i - 1] == c)
			{
				ret[j] = (char *)&s[i];
				j++;
			}
			i++;
		}
	}
	return (ret);
}

static char	**ft_getpartsend(char const *s, char c, size_t amount)
{
	size_t	i;
	size_t	j;
	char	**ret;

	ret = (char **)malloc((amount + 1) * sizeof(char *));
	if (ret)
	{
		i = 0;
		j = 0;
		while (s[i] != '\0')
		{
			if (i > 0 && s[i] == c && s[i - 1] != c)
			{
				ret[j] = (char *)&s[i];
				j++;
			}
			else if (i > 0 && s[i] != c && s[i + 1] == '\0')
			{
				ret[j] = (char *)&s[i + 1];
				j++;
			}
			i++;
		}
	}
	return (ret);
}

static char	**splitfree(char **arr, char **p_s, char **p_e, size_t amount)
{
	size_t	i;

	if (arr)
	{
		i = 0;
		while (i < amount)
		{
			if (arr[i])
				free(arr[i]);
			i++;
		}
		free(arr);
	}
	if (p_s)
		free(p_s);
	if (p_e)
		free(p_e);
	return (NULL);
}

/**
 * Split a string on certain characters
 * @param *s	The string to split
 * @param c		The character to split the string at
 * @return		An array of strings containing the split up string,
 * 				NULL on error, array ends with NULL
 */
char	**ft_split(char const *s, char c)
{
	char	**arr;
	char	**p_start;
	char	**p_end;
	size_t	i;
	size_t	p_amount;

	p_amount = ft_getsepsamount(s, c);
	arr = (char **)malloc((p_amount + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	p_start = ft_getpartsstart(s, c, p_amount);
	p_end = ft_getpartsend(s, c, p_amount);
	i = 0;
	if (!p_start || !p_end)
		return (splitfree(arr, p_start, p_end, p_amount));
	while (i < p_amount)
	{
		arr[i] = ft_substr(s, p_start[i] - s, p_end[i] - p_start[i]);
		if (!arr[i])
			return (splitfree(arr, p_start, p_end, p_amount));
		i++;
	}
	splitfree(NULL, p_start, p_end, p_amount);
	arr[i] = 0;
	return (arr);
}
