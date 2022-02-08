#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"
#include "envars.h"
#include "custom_errors.h"

int	mini_cd(t_cmd *cmd)
{
	t_envar	*envar;
	char	*path;
	int		ret;

	if (cmd->params[1])
		path = cmd->params[1];
	else
	{
		envar = get_envar(cmd->mini->envars, "HOME");
		if (!envar)
			exit_shell_w_error(cmd, ERR_ENV_NOT_SET);
		path = envar->val;
	}
	if (chdir(path) < 0)
		return (errno);
	path = getcwd(NULL, 0);
	if (!path)
		return (ENOMEM);
	envar = get_envar(cmd->mini->envars, "PWD");
	if (!envar && !set_envar(cmd->mini, "PWD", path, 0))
	{
		free(path);
		return (ENOMEM);
	}
	if (!replace_envar_value(envar, path))
		return (ENOMEM);
	free(path);
	return (0);
}
