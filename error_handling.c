#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "utils.h"

void	force_exit(t_mini *mini, int err)
{
	free_mini(mini);
	exit(err);
}
