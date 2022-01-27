#include "include/structs.h"
#include "include/custom_errors.h"
#include "include/parse.h"
#include "include/debug.h"
#include "include/error_handling.h"
#include <stdio.h>

//MANAGE THE MEMORY STRTRIM IS ALLOCATING CONTINUOUSLY


int	next_operator_index(char **prompt, char *set)
{
	int		next_operator;
	char	*trim;

	trim = ft_strtrim(*prompt, " ");
	if (!(*trim))
		return (ENOMEM);
	*prompt = trim;
	if (**prompt == *set)
		return (-1);
	next_operator = scan_operators(*prompt, set);
	if (*(*prompt + next_operator) == '\0')
		return (next_operator);
	if (*(*prompt + next_operator + 1) == *set)
		return (-1);
	return(next_operator);
}

int	split_prompt(char *from, char ***to, char *set)
{
	int		ret;
	int		next_operator;
	char	*split;

	ret = 0;
	while (*from)
	{
		next_operator = next_operator_index(&from, set);
		if (next_operator < 0)
			return(PARSE_ERROR);
		//if theres only spaces until \0 just return 0 and not split.. this way you dont have to reallocate with trim?
		split = ft_substr(from, 0, next_operator);
		if (!split)
			return (ENOMEM);
		if (split[0] != '\0')
			ret = add_string_to_array(to, split);
		if (ret != 0)
			return (ret);
		from += next_operator;
		if (*from != '\0')
			from++;
	}
	return (0);
	
}

int	parse_prompt(t_mini *mini, char *prompt)
{
	char	**prompt_split;
	int		ret;

	if (*prompt)
	{
		prompt_split = ft_calloc(1, sizeof(char *));
		if (!prompt_split)
			force_exit(mini, ENOMEM);
		ret = split_prompt(prompt, &prompt_split, ";");
		if (ret != 0)
			return (ret);
		print_char_array(prompt_split);
	}
	free(prompt);
	return (0);
}
