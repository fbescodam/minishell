/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_params.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jgalloni <jgalloni@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/08 22:51:44 by jgalloni      #+#    #+#                 */
/*   Updated: 2022/04/18 16:58:03 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "utils.h"
#include <stdlib.h>
#include <debug.h>
#include <stdio.h>

static int	close_param(char **buff, char **prompt, int len, char ***dest)
{
	int	err;

	err = join_realloc(buff, *prompt, len);
	if (err != 0)
		return (-1);
	err = add_param(buff, dest);
	if (err != 0)
		return (-1);
	*prompt += len;
	while (**prompt == ' ')
		(*prompt)++;
	return (0);
}

static int	handle_quotes(char **buff, char **prompt, int quote_pos)
{
	char	*quoted_string;
	int		err;
	int		str_len;

	err = join_realloc(buff, *prompt, quote_pos);
	if (err < 0)
		return (-1);
	err = get_quoted_string(*prompt + quote_pos, &quoted_string);
	if (err < 0)
		return (-1);
	str_len = ft_strlen(quoted_string);
	err = join_realloc(buff, quoted_string, str_len);
	free(quoted_string);
	if (err != 0)
		return (-1);
	*prompt += str_len + quote_pos + 2;
	return (0);
}

int	add_param(char **param_buffer, char ***dest)
{
	char	*param;
	int		err;

	err = 0;
	param = ft_strdup(*param_buffer);
	if (!param)
		return (-1);
	if (*param)
		err = add_string_to_array(dest, param);
	else
		free(param);
	free(*param_buffer);
	if (err != 0)
		return (-1);
	*param_buffer = ft_strdup("");
	if (!*param_buffer)
		return (-1);
	return (0);
}

int	search_params(char **buff, char **prompt, char ***dest)
{
	int	nxt_delim;
	int	nxt_quote;
	int	ret;

	ret = 0;
	if (is_fd_redir(*prompt))
		return (1);
	nxt_delim = scan_operators(*prompt, " <>", 0);
	nxt_quote = scan_operators(*prompt, "\'\"", 0);
	if (nxt_delim <= nxt_quote)
		ret = close_param(buff, prompt, nxt_delim, dest);
	else
		ret = handle_quotes(buff, prompt, nxt_quote);
	if (ret != 0)
		return (-1);
	if (**prompt == '<' || **prompt == '>' || **prompt == '\0')
		return (1);
	return (0);
}

int	parse_params(char *prompt, char ***dest)
{
	char	*prompt_start;
	char	*buff;
	int		ret;

	prompt_start = prompt;
	buff = ft_strdup("");
	if (!buff)
		return (-1);
	ret = 0;
	while (ret == 0)
	{
		ret = search_params(&buff, &prompt, dest);
		if (ret == -1)
			return (-1);
	}
	if (*buff)
		ret = add_param(&buff, dest);
	if (ret < 0)
		return (-1);
	free(buff);
	return (prompt - prompt_start);
}
