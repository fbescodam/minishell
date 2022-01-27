#include <stdlib.h>
#include "libft.h"
#include "structs.h"
#include "utils.h"
#include "envars.h"
	#include <stdio.h>

static int	parse_envar_fail(int err, char *parsed_str)
{
	printf("envar parse error occurred: %d\n", err);	// TODO remove this
	ft_free(parsed_str);
	return (err);
}

static int	join_parsed_str(char **parsed_str, char *str)
{
	char	*temp;

	temp = ft_strjoin(*parsed_str, str);
	if (!temp)
		return (0);
	free(*parsed_str);
	*parsed_str = temp;
	return (1);
}

static int	fetch_n_replace_envar(t_dlist *envars, char **parsed_str,
	char **var_start, char **var_end)
{
	t_envar	*envar;
	char	*var_name;
	char	*temp;

	if (**var_start == '{')
		*(*var_start - 1) = '\0';
	**var_start = '\0';
	if (!join_parsed_str(parsed_str, *var_end))
		return (-1);
	*var_end = find_var_name_end(*var_start + 1);
	if (!*var_end)
		return (-2);
	var_name = ft_substr(*var_start + 1, 0, *var_end - *var_start - 1);
	if (!var_name)
		return (-1);
	temp = ft_strchr(var_name, '}');
	if (temp)
		*temp = '\0';
	envar = get_envar(envars, var_name);
	free(var_name);
	if (envar && !join_parsed_str(parsed_str, envar->val))
		return (-1);
	if (!find_var_name_start(*var_start + 1, var_start))
		return (-3);
	return (0);
}

static int	replace_str_with_parsed(char **str, char *parsed_str, char *var_end)
{
	if (*parsed_str != '\0')
	{
		if (!join_parsed_str(&parsed_str, var_end))
			return (-1);
		ft_free(*str);
		*str = parsed_str;
	}
	remove_character(str, '\'');
	remove_character(str, '\"');
	return (0);
}

/**
 * @brief Find and replace environment variables in a string
 *
 * @param envars A list of environment variables
 * @param str A pointer to the string to search and replace in
 * @return Returns -1 on ENOMEM, -2 on syntax error, -3 on unclosed single quote
 */
int	parse_envars(t_dlist *envars, char **str)
{
	char	*parsed_str;
	char	*var_start;
	char	*var_end;
	int		ret;

	// TODO free parsed_str before return, use parse_envar_fail
	parsed_str = ft_calloc(1, sizeof(char));
	if (!parsed_str)
		return (-1);
	if (!find_var_name_start(*str, &var_start))
		return (-3);
	var_end = *str;
	while (var_start && *var_start)
	{
		ret = fetch_n_replace_envar(envars, &parsed_str, &var_start, &var_end);
		if (ret < 0)
			return (ret);
	}
	return (replace_str_with_parsed(str, parsed_str, var_end));
}
