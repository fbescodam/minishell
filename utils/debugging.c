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
