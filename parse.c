#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "libft/libft.h"
#include <stdlib.h>
#include <signal.h>
#include "readline/readline.h"
#include "readline/history.h"
#include "utils.h"
#include "tokens.h"
#include "custom_errors.h"
#include "parse.h"

int	parse_command(t_list *cmds, char *prompt)
{
	int	ret;

	ret = tokenize(prompt, &cmds);
	if (ret == PARSE_ERROR)
	{
		printf("minishell: syntax error\n");
		errno = PARSE_ERROR;
		return (0);
	}
	if (ret != 0)
		exit_shell_w_error((t_cmd *)(cmds->content), ret);
	if (!(((t_cmd *)(cmds->content))->tokens))
		return (0);
	return (1);
}

int		split_prompt(char *prompt, char ***prompts, char *c)
{
	int		ret;
	int		i;
	int		next_operator;
	char	*split;

	i = 0;
	ret = 0;
	while (prompt[i])
	{
		next_operator = scan_operators(prompt + i, c);
		if (prompt[i + next_operator] + 1 == *c)
			return(PARSE_ERROR);
		split = ft_substr(prompt + i, 0, next_operator);
		if (!split)
			return (ENOMEM);
		if (split[0] != '\0')
			ret = add_string_to_array(prompts, split);
		if (ret != 0)
			return (ret);
		i += next_operator;
		if (prompt[i] != '\0')
			i++;
	}
	return (0);
}

int	parse_prompt(char *prompt, t_list *cmds, t_mini *mini)
{
	size_t	i;
	char	**prompts;
	int		ret;

	if (prompt && *prompt)
	{
		if (prompt[0] == ';')
			return (PARSE_ERROR);
		prompts = ft_calloc(1, sizeof(char *));
		ret = split_prompt(prompt, &prompts, ";");
		i = 0;
		while (prompts[i])
		{
			ret = setup_cmds(mini, &cmds);
			if (ret != 0)
				exit_shell_w_error(NULL, ret);
			ret = parse_command(cmds, prompts[i]);
			if (ret)
				execute_command((t_cmd *)(cmds->content), mini->paths);
			i++;
			ft_lstclear(&cmds, &free_cmd);
		}
		ft_free_double_ptr((void **)prompts);
		add_history(prompt);
	}
	ft_free(prompt);
	return(ret);
}
