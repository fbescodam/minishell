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
		printf("FLAG: %d, CONTENT: %s, FD: %d\n", token->flag, (char *)(token->content), token->fd);
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

void	print_command_status(t_cmd *cmd, int ret)
{
	if (ret == -1)
		printf("Command not found: %s\n", *(cmd->params));
	else if (ret == 0 && cmd->path)
		printf("Command %s found at path :'%s'\n", *(cmd->params), cmd->path);
	else
		printf("No command in this prompt. cmd->path %s \n", cmd->path);
}

void	print_path_pid(t_list *cmds, int pid)
{
	t_list	*current;
	t_cmd	*cmd;

	current = cmds;
	while (current)
	{
		cmd = (t_cmd *)current->content;
		if (cmd->pid == pid)
		{
			printf("COMMAND: %s\n", cmd->path);
			break ;
		}
		current = current->next;
	}
}
