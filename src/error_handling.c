#include <stdio.h>
#include <stdlib.h>
#include "readline/readline.h"
#include "structs.h"
#include "utils.h"
#include "custom_errors.h"

void	force_exit(t_mini *mini, int err)
{
	free_mini(mini);
	rl_clear_history();
	system("leaks minishell");
	if (!err)
		exit(mini->status);
	else
		exit(err);
}

void	error_manager(t_mini *mini, int err)
{
	mini->status = err;
	if (err == PARSE_ERROR)
		ft_putstr_fd("minishell: parse error\n", 2);
	else if (err == CMDNF)
		ft_putstr_fd("minishell: command not found\n", 2);
	else if (err > 0)
		perror("minishell: ");
	else if (err < 0)
	{
		if (err == ERR_ENV_NOT_SET)
			ft_putstr_fd("minishell: expected environment variable missing", 2);
	}
	else if (err == 0)
		ft_putstr_fd("minishell: an unknown error occurred (exit code 0?)", 2);
}
