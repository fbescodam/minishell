#include <stdlib.h>
#include <errno.h>
#include "libft.h"
#include "utils.h"
#include "envars.h"
	#include <stdio.h>

static int	is_valid_env_name_char(size_t pos, char c)
{
	if (pos == 0)
	{
		if (c != '_' && !ft_isalpha(c))
			return (0);
	}
	else if (c != '_' && !ft_isalnum(c))
		return (0);
	return (1);
}

/**
 * @brief Find the start of a variable name in a string
 *
 * @param[in] str The string to search through
 * @param[in] var_start A pointer which will be set to the next start of a variable
 * @return Returns 0 on unclosed single quote, 1 on success (also if no var!)
 */
int	find_var_name_start(char *str, char **var_start)
{
	char	*dollar;
	char	*squote;

	squote = get_next_single_quote(str);
	dollar = ft_strchr(str, '$');
	//printf("before dollar: %p %s\n", dollar, dollar);
	//printf("before squote: %p %s\n", squote, squote);
	while (dollar && squote && squote < dollar)
	{
		str = get_next_single_quote(squote + 1);
		if (!str)
			return (0);
		dollar = ft_strchr(str, '$');
		squote = get_next_single_quote(str + 1);
		//printf("while dollar: %p %s\n", dollar, dollar);
		//printf("while squote: %p %s\n", squote, squote);
	}
	//printf("after dollar: %p %s\n", dollar, dollar);
	//printf("after squote: %p %s\n", squote, squote);
	if (dollar && *(dollar + 1) == '{')
		dollar++;
	*var_start = dollar;
	return (1);
}

/**
 * @brief Find the end of a variable name in a string
 *
 * @param[in] str the start of a variable name in the string, right after the $
 * @return char* the end of said variable, points to the char after the var
 */
char	*find_var_name_end(char *str, char is_curly_bracket)
{
	char	*chr;
	size_t	i;

	if (is_curly_bracket > '\0')
	{
		chr = ft_strchr(str, '}');
		if (chr == str)
			return (NULL);
		if (chr)
			chr++;
		return (chr);
	}
	i = 0;
	chr = str;
	while (is_valid_env_name_char(0, *chr))
		chr++;
	if (ft_strchr(RESERVED_ENVAR_NAMES, *chr) && chr == str)
		return (chr + 1);
	return (chr);
}

int	set_mini_paths(t_mini *mini, t_ditem *list_item)
{
	if (mini->paths)
		ft_free_double_ptr((void **)mini->paths);
	mini->paths = ft_split(((t_envar *)list_item->content)->val, ':');
	if (!mini->paths)
	{
		ft_dlstdelone(list_item, &free_envar);
		return (0);
	}
	return (1);
}

int	set_mini_status(t_mini *mini, int status_code)
{
	t_envar	*quest;
	char	*stat;
	int		ret;

	stat = ft_itoa(status_code);
	if (!stat)
		return (0);
	mini->status = status_code;
	quest = get_envar(mini->envars, "?");
	if (quest)
		ret = replace_envar_value(quest, stat);
	else
		ret = set_envar(mini, "?", stat, 0);
	free(stat);
	return (ret);
}

// stop at '=' because that is where the value starts if used in
// parse_set_envars_b4_comm. TODO: might introduce bugs?
int	is_valid_env_name(char *name)
{
	size_t	i;

	if (!is_valid_env_name_char(0, *name))
		return (0);
	i = 1;
	while (name[i] && name[i] != '=')
	{
		if (!is_valid_env_name_char(i, name[i]))
			return (0);
		i++;
	}
	return (1);
}
