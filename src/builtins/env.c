#include <stdio.h>
#include "utils.h"

// TODO: env runs in the child, because it doesn't change any memory
int	mini_env(t_cmd *cmd)
{
	t_list	*temp;

	temp = cmd->mini->envars;
	while (temp)
	{
		printf("%s=%s\n", ((t_envar *)temp->content)->name,
			((t_envar *)temp->content)->val);
		temp = temp->next;
	}
	return (0);
}
