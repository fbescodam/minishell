#include <stdio.h>
#include "error_handling.h"
#include "utils.h"

// exit runs in the parent. the exit is not printed in out with exit > out
int	mini_exit(t_cmd *cmd)
{
	printf("exit\n");
	if (char_array_len(cmd->params) > 1)
	{
		printf("minishell: exit codes are not implemented (not required)\n");
		// maybe it is after all? "no arguments" is not stated in the subject
		// but it is stated for env, so maybe arguments != options in subject
	}
	force_exit(cmd->mini, 1);
	return (0);
}
