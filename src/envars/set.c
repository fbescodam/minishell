/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 20:45:54 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/08 22:58:52 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "libft.h"
#include "utils.h"
#include "envars.h"
	#include <stdio.h>

/**
 * @brief Set the new start of str, free the old str and replace it with dup
 *
 * @param[in] str The str, what else?
 * @param[in] new_start The last pos that was checked in parse_set_envars_b4_comm
 * @param[in] end_of_str A pointer to the last NULL character of new_start string
 * @return Returns 1 on success, 0 on error
 */
static int	set_new_start(char **str, char *last_c, char *start, char *end)
{
	char	*temp;
	size_t	i;

	if (last_c > end)
	{
		temp = ft_strdup("");
		if (!temp)
			return (0);
	}
	else
	{
		while (*last_c != '\0' && last_c != start)
			last_c--;
		if (last_c != start && last_c != end)
			last_c++;
		temp = (char *)malloc(end - last_c + 1);
		if (!temp)
			return (0);
		i = 0;
		while (last_c < end)
		{
			if (*last_c != '\0')
				temp[i] = *last_c;
			else
				temp[i] = ' ';
			last_c++;
			i++;
		}
		temp[i] = '\0';
	}
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
 * @param[in] str The string to parse one
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
	size_t	i;
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
