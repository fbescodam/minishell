/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envars.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 17:58:55 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/24 19:23:01 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "errno.h"
	#include <stdio.h>

/**
 * @brief Get an environment variable from the list
 *
 * @param list This pointer will point to the list item if it is found
 * @param envars The list of envars to search through
 * @param name The name of the environment variable to find
 * @return int The index of the environment variable in the list
 */
int	get_envar_as_list(t_list **list, t_list *envars, char *name)
{
	int		i;
	t_list	*temp;
	size_t	name_len;

	name_len = ft_strlen(name);
	temp = envars;
	i = 0;
	while (temp)
	{
		if (ft_strncmp(((t_envar *)temp->content)->name, name, name_len) == 0)
		{
			*list = temp;
			return (i);
		}
		temp = temp->next;
		i++;
	}
	*list = NULL;
	return (-1);
}

/**
 * @brief Get an environment variable from the list
 *
 * @param envar This pointer will point to the envar if it is found
 * @param envars The list of envars to search through
 * @param name The name of the environment variable to find
 * @return int The index of the environment variable in the list
 */
int	get_envar(t_envar **envar, t_list *envars, char *name)
{
	t_list	*temp;
	int		index;

	index = get_envar_as_list(&temp, envars, name);
	if (index > -1)
		*envar = (t_envar *)temp->content;
	else
		*envar = NULL;
	return (index);
}

t_envar	*set_envar(t_cmd *cmd, char *name, char *val)
{
	t_envar		*envar;
	t_list		*list_elem;

	get_envar(&envar, cmd->mini->envars, name);
	if (envar)
	{
		ft_free(envar->val);
		envar->val = ft_strdup(val);
		if (!envar->val)
			exit_shell_w_error(cmd, ENOMEM);
		return (0);
	}
	envar = ft_calloc(1, sizeof(t_envar));
	if (!envar)
		exit_shell_w_error(cmd, ENOMEM);
	envar->name = ft_strdup(name);
	envar->val = ft_strdup(val);
	list_elem = ft_lstnew(envar);
	if (!list_elem || !envar->name || !envar->val)
	{
		free_envar(envar);
		ft_free(list_elem);
		exit_shell_w_error(cmd, ENOMEM);
	}
	ft_lstadd_back(&(cmd->mini->envars), (void *)list_elem);
	return (envar);
}

/**
 * @brief Find the end of a variable name in an argument
 *
 * @param str the start of a variable name in the argument, right after the $
 * @return char* the end of said variable, points to the char after the var
 */
static char	*find_var_name_end(char *str)
{
	char	*chr;

	if (*str == '{')
	{
		chr = ft_strchr(str, '}');
		if (chr)
			chr++;
		return (chr);
	}
	chr = ft_strschr(str, " $=\"");
	if (chr)
		return (chr);
	return (ft_strchr(str, '\0'));
}

static int	parse_envar_fail(int err, char *parsed_str)
{
	printf("envar parse error occurred: %d\n", err);	// TODO remove this
	ft_free(parsed_str);
	return (err);
}

static int skip_over_single_quotes(char **str)
{
	char	*temp;

	temp = ft_strchr(*str + 1, '\'');
	if (!temp)
		return (0);
	*str = temp;
	return (1);
}

static void	remove_character(char **str, char rem)
{
	char	any_change;
	char	*quote;

	any_change = 0;
	quote = ft_strchr(*str, rem);
	//printf("input: \"%s\"\n", *str);
	while (quote)
	{
		//printf("found a quote: \"%s\"\n", quote);
		any_change = 1;
		ft_memmove(quote, quote + 1, ft_strlen(quote));
		quote = ft_strchr(quote, rem);
	}
	if (!any_change)
		return ;
	quote = ft_strdup(*str);
	if (quote)
	{
		free(*str);
		*str = quote;
	}
}

// see http://www.compciv.org/topics/bash/variables-and-substitution/
// returns -1 on ENOMEM and -2 on syntax error, -3 on unclosed single quote
int	parse_envars(t_list *envars, char **str)
{
	char	*temp;
	char	*dollar;
	char	*var_end;
	char	*var_name;
	char	*parsed_str;
	t_envar	*envar;

	//printf("begin *str: \"%s\"\n", *str);
	parsed_str = ft_calloc(1, sizeof(char));
	if (!parsed_str)
		return (-1);
	dollar = ft_strschr(*str, "$\'");
	while (dollar && *dollar != '$')
	{
		if (!*dollar)
			break ;
		if (dollar && *dollar == '\'' && !skip_over_single_quotes(&dollar))
			return (parse_envar_fail(-3, parsed_str));
		dollar = ft_strschr(dollar + 1, "$\'");
	}
	var_end = *str;
	while (dollar && *dollar)
	{
		//printf("var_name start: \"%s\"\n", dollar + 1);
		*dollar = '\0';
		temp = ft_strjoin(parsed_str, var_end);
		if (!temp)
			return (parse_envar_fail(-1, parsed_str));
		ft_free(parsed_str);
		parsed_str = temp;
		var_end = find_var_name_end(dollar + 1);
		if (!var_end)
			return (parse_envar_fail(-2, parsed_str));
		if (*(dollar + 1) == '{')
			dollar++;
		//printf("var_name end: \"%s\"\n", var_end);
		var_name = ft_substr(dollar + 1, 0, var_end - dollar - 1);
		if (!var_name)
			return (parse_envar_fail(-1, parsed_str));
		temp = ft_strchr(var_name, '}');
		if (temp)
			*temp = '\0';		// hacky way of removing } from name
		//printf("var_name: \"%s\"\n", var_name);
		get_envar(&envar, envars, var_name);
		free(var_name);
		if (envar)
		{
			//printf("var value: \"%s\"\n", envar->val);
			temp = ft_strjoin(parsed_str, envar->val);
			if (!temp)
				return (parse_envar_fail(-1, parsed_str));
			ft_free(parsed_str);
			parsed_str = temp;
		}
		//printf("new *str: \"%s\"\n", parsed_str);
		dollar = ft_strschr(dollar + 1, "$\'");
		while (dollar && *dollar != '$')
		{
			if (!*dollar)
				break ;
			if (dollar && *dollar == '\'' && !skip_over_single_quotes(&dollar))
				return (parse_envar_fail(-3, parsed_str));
			dollar = ft_strschr(dollar + 1, "$\'");
		}
	}
	if (ft_strlen(parsed_str) > 0)
	{
		temp = ft_strjoin(parsed_str, var_end);
		if (!temp)
			return (parse_envar_fail(-1, parsed_str));
		ft_free(parsed_str);
		ft_free(*str);
		*str = temp;
		//printf("[!!] *str changed! ");
	}
	remove_character(str, '\'');
	remove_character(str, '\"');
	//printf("final *str: \"%s\"\n", *str);
	return (0);
}
