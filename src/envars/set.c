/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 20:45:54 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/09 00:50:46 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "libft.h"
#include "utils.h"
#include "envars.h"

static int	set_new_start_inner(char **temp, char **last_c,
		char *start, char *end)
{
	size_t	i;

	while (**last_c != '\0' && *last_c != start)
		(*last_c)--;
	if (*last_c != start && *last_c != end)
		(*last_c)++;
	*temp = ft_stralloc(end - *last_c);
	if (!*temp)
		return (0);
	i = 0;
	while (*last_c < end)
	{
		if (**last_c != '\0')
			(*temp)[i] = **last_c;
		else
			(*temp)[i] = ' ';
		(*last_c)++;
		i++;
	}
	return (1);
}

static int	set_new_start(char **str, char *last_c,
		char *start, char *end)
{
	char	*temp;

	if (last_c > end)
	{
		temp = ft_strdup("");
		if (!temp)
			return (0);
	}
	else if (!set_new_start_inner(&temp, &last_c, start, end))
		return (0);
	ft_free(*str);
	*str = temp;
	return (1);
}

static int	all_done(char *temp, int ret)
{
	ft_free(temp);
	return (ret);
}

/**
 * @brief Perform magic
 *
 * @param[in] mini The mini struct
 * @param[in] str The string to parse
 * @return Returns 1 on success, 0 on error, -1 on done
 */
static int	set_one_envar(t_mini *mini, char **str)
{
	char	*equals_pos;
	char	*value;
	int		ret;

	equals_pos = ft_strchr(*str, '=');
	if (!equals_pos)
		return (-1);
	if (!is_valid_env_name(*str))
		return (-1);
	*equals_pos = '\0';
	value = ft_strdup(equals_pos + 1);
	if (!value)
		return (0);
	if (parse_envars(mini->envars, &value) != 0)
		return (0);
	ret = set_envar(mini, *str, value, 0);
	free(value);
	*str = ft_strchr(equals_pos + 1, '\0');
	return (ret);
}

/**
 * @brief Parse and set environment variables before running a command
 *
 * @param[in] mini The mini struct
 * @param[in] str The whole input from readline
 * @return Returns 0 on success, else on error
 */
int	parse_set_envars_b4_comm(t_mini *mini, char **str)
{
	char	*temp;
	char	*end_of_str;
	int		ret;
	char	*cur;

	temp = ft_strmapi(*str, &replace_space_with_null);
	end_of_str = temp + ft_strlen(*str);
	cur = temp;
	while (cur < end_of_str)
	{
		ret = set_one_envar(mini, &cur);
		if (ret == 0)
			return (all_done(temp, ENOMEM));
		else if (ret == -1)
			break ;
		cur++;
	}
	if (!set_new_start(str, cur, temp, end_of_str))
		return (all_done(temp, ENOMEM));
	return (all_done(temp, 0));
}
