#include <stdio.h>
#include "utils.h"

// TODO: env runs in the child, because it doesn't change any memory
int	mini_env(t_cmd *cmd)
{
	size_t	i;
	t_ditem	*item;

	i = 0;
	item = cmd->mini->envars->first;
	while (i < cmd->mini->envars->size)
	{
		if (((t_envar *)item->content)->export)
			printf("%s=%s\n", ((t_envar *)item->content)->name,
				((t_envar *)item->content)->val);
		item = item->next;
		i++;
	}
	return (0);
}
