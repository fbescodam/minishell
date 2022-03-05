#include <stdio.h>
#include "error_handling.h"
#include "utils.h"
#include "envars.h"

// error code 255, like bash
static void	exit_err(t_cmd *cmd, char *str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": numeric argument required", 2);
	set_mini_status(cmd->mini, 255);
}

// exit runs in the parent. the exit is not printed in out with exit > out
int	mini_exit(t_cmd *cmd)
{
	char	*temp;

	ft_putendl_fd("exit", 2);
	if (char_array_len(cmd->params) > 1)
	{
		temp = cmd->params[1];
		while (*temp)
		{
			if (!ft_isdigit(*temp) && *temp != '-')
				break ;
			temp++;
		}
		if (!*temp)
			set_mini_status(cmd->mini,
				(int)(unsigned char)ft_atoi(cmd->params[1]));
		else
			exit_err(cmd, cmd->params[1]);
	}
	force_exit(cmd->mini, 0);
	return (0);
}
