
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "utils.h"
#include "custom_errors.h"

void	force_exit(t_mini *mini, int err)
{
	free_mini(mini);
	exit(err);
}

void	error_manager(t_mini *mini, int err)
{
	if (err == PARSE_ERROR)
	{
		ft_putstr_fd("minishell: parse error\n", 2);
		mini->status = PARSE_ERROR;
	}
}
