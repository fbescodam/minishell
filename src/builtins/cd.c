#include "utils.h"
#include "envars.h"
#include "custom_errors.h"
#include <errno.h>

int	mini_cd(t_cmd *cmd)
{
	t_envar	*home;
	int		ret;

	if (cmd->params[1])
		ret = chdir(cmd->params[1]);
	else
	{
		home = get_envar(cmd->mini->envars, "HOME");
		if (!home)
			exit_shell_w_error(cmd, ERR_ENV_NOT_SET);
		ret = chdir(home->val);
	}
	if (ret < 0)
		return (errno);
	return (0);
}
