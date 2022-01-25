#include "structs.h"
#include <stdio.h>

void print_envars(t_mini *mini)
{
	t_list *current;

	current = mini->envars;
	while (current)
	{
		printf("%s\n", (char *)(current->content));
		current = current->next;
	}
}
