#include <stdlib.h>
#include "libft.h"
#include "structs.h"
#include "utils.h"
#include "envars.h"
#include "custom_errors.h"
	#include <stdio.h>

static int	parse_envar_fail(char *parsed_str, int err)
{
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
	else
		**var_start = '\0';
	if (!join_parsed_str(parsed_str, *var_end))
		return (ENOMEM);
	*var_end = find_var_name_end(*var_start + 1, **var_start);
	if (!*var_end)
		return (PARSE_ERROR);
	if (*var_end == *var_start + 1)
	{
		if (!join_parsed_str(parsed_str, "$"))
			return (ENOMEM);
		return (0);
	}
	var_name = ft_substr(*var_start + 1, 0, *var_end - *var_start - 1);
	//printf("var_name: \"%s\"\n", var_name);
	if (!var_name)
		return (ENOMEM);
	temp = ft_strchr(var_name, '}');
	if (temp)
		*temp = '\0';
	envar = get_envar(envars, var_name);
	free(var_name);
	if (envar && !join_parsed_str(parsed_str, envar->val))
		return (ENOMEM);
	if (!find_var_name_start(*var_end, var_start))
		return (0);
	return (0);
}

static int	replace_str_with_parsed(char **str, char *parsed_str, char *var_end)
{
	if (*parsed_str != '\0')
	{
		if (!join_parsed_str(&parsed_str, var_end))
			return (parse_envar_fail(parsed_str, ENOMEM));
		ft_free(*str);
		*str = parsed_str;
	}
	else
		ft_free(parsed_str);
	return (0);
}

/**
 * @brief Find and replace environment variables in a string, plus parse ones
 * set with var=value before any commands
 *
 * @param[in] envars A list of environment variables to work with
 * @param[in] str A pointer to the string to search and replace in
 * @return Returns 0 on success, everything else is an error (see error_manager)
 */
int	parse_envars(t_dlist *envars, char **str)
{
	char	*parsed_str;
	char	*var_start;
	char	*var_end;
	int		ret;

	if (!find_var_name_start(*str, &var_start))
		return (parse_envar_fail(NULL, 0));
	if (!var_start || !*var_start)
		return (0);
	parsed_str = ft_calloc(1, sizeof(char));
	if (!parsed_str)
		return (parse_envar_fail(parsed_str, ENOMEM));
	var_end = *str;
	while (var_start && *var_start)
	{
		ret = fetch_n_replace_envar(envars, &parsed_str, &var_start, &var_end);
		if (ret != 0)
			return (parse_envar_fail(parsed_str, ret));
	}
	return (replace_str_with_parsed(str, parsed_str, var_end));
}
