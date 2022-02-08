#include "structs.h"
#include <stdio.h>

void	print_envars(t_mini *mini)
{
	t_ditem		*current;

	current = mini->envars->first;
	while (current)
	{
		printf("%s=%s\n", ((t_envar *)current->content)->name, ((t_envar *)current->content)->val);
		current = current->next;
	}
}

void	print_char_array(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		printf("STR:%s:\n", arr[i]);
		i++;
	}
}

void	print_tokens(t_list *tokens)
{
	t_list *current;
	t_token *token;

	current = tokens;
	while (current)
	{
		token = (t_token *)(current->content);
		printf("FLAG: %d, CONTENT: %s\n", token->flag, (char *)(token->content));
		current = current->next;
	}
}

void	print_command_list(t_list *cmds)
{
	t_list *current;
	t_cmd *cmd;

	current = cmds;
	while (current)
	{
		cmd = (t_cmd *)(current->content);
		printf("COMMAND PARAMS: \n");
		print_char_array(((t_cmd *)(current->content))->params);
		printf("COMMAND TOKENS : \n");
		print_tokens(((t_cmd *)(current->content))->tokens);
		current = current->next;
	}
}
