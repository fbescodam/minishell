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

int	parse_command(t_list *cmds, char *prompt)
{
	int	ret;

	ret = tokenize(prompt, &cmds);
	if (ret != 0 && ret != -1)
		return (ret);
	if (!(((t_cmd *)(cmds->content))->tokens))
		return (-1);
	return (0);
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

int	split_pipe(char	*prompt, t_list **cmds, t_mini *mini)
{
	int		ret;
	char	**commands;
	int		i;
	t_list	*current_cmd;
	int		*fd;

	if (prompt[0] == '|')
		return (PARSE_ERROR);
	commands = ft_calloc(1, sizeof(char *));
	ret = split_prompt(prompt, &commands, "|");
	i = 0;
	while (commands[i])
	{
		current_cmd = setup_cmds(mini, cmds);
		if (current_cmd == NULL)
				exit_shell_w_error(NULL, ret);
		if (i > 0)
			pipe_in(current_cmd->content, &fd);
		ret = parse_command(current_cmd, commands[i]);
		if (ret != 0 && ret != -1)
			return (ret);
		if (commands[i + 1])
			pipe_out(current_cmd->content, &fd);
		i++;
	}
	free(commands);
	return (0);
}

void	execute_command_list(t_list *cmds, t_mini *mini)
{
	t_list	*current;

	current = cmds;
	while(current != NULL)
	{
		execute_command((t_cmd *)(current->content), mini->paths);
		current = current->next;
	}
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
			ret = split_pipe(prompts[i], &cmds, mini);
			i++;		
		}
		execute_command_list(cmds, mini);
		ft_lstclear(&cmds, &free_cmd);
		ft_free_double_ptr((void **)prompts);
		add_history(prompt);
	}
	ft_free(prompt);
	return(ret);
}
