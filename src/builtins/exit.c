#include <stdio.h>
#include "error_handling.h"
#include "utils.h"
#include "envars.h"

// error code 255 on weird exit codes, like in bash
static int	exit_err(int is_child, t_cmd *cmd, char *str)
{
	if (is_child)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": numeric argument required", 2);
		return (0);
	}
	force_exit(cmd->mini, 255);
	return (0);
}

// exit runs in the child. the exit is printed out on FD 2, just like in bash.
int	mini_exit(int is_child, t_cmd *cmd)
{
	char	*temp;

	if (is_child)
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
		{
			if (is_child)
				return (0);
			cmd->mini->status = (int)(unsigned char)ft_atoi(cmd->params[1]);
		}
		else
			return (exit_err(is_child, cmd, cmd->params[1]));
	}
	force_exit(cmd->mini, cmd->mini->status);
	return (0);
}
