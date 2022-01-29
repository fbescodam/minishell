#include "../libft/libft.h"
#include "utils.h"

/**
 * @brief Find the start of a variable name in a string
 *
 * @param str The string to search through
 * @param var_start A pointer which will be set to the next start of a variable
 * @return Returns 0 on unclosed single quote, 1 on success (also if no var!)
 */
int	find_var_name_start(char *str, char **var_start)
{
	char	*dollar;

	dollar = ft_strschr(str, "$\'");
	while (dollar && *dollar != '$')
	{
		if (!*dollar)
			break ;
		if (dollar && *dollar == '\'' && !skip_over_single_quotes(&dollar))
			return (0);
		dollar = ft_strschr(dollar + 1, "$\'");
	}
	if (dollar && *(dollar + 1) == '{')
		dollar++;
	*var_start = dollar;
	return (1);
}

/**
 * @brief Find the end of a variable name in a string
 *
 * @param str the start of a variable name in the string, right after the $
 * @return char* the end of said variable, points to the char after the var
 */
char	*find_var_name_end(char *str)
{
	char	*chr;

	if (*(str - 1) == '{')
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
