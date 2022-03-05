#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"
#include "envars.h"
#include "custom_errors.h"

// TODO: cd runs in the parent
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
			return (ERR_ENV_NOT_SET);
		path = envar->val;
	}
	if (chdir(path) < 0)
	{
		if (!ptc_error(cmd, strerror(errno)))
			return (ENOMEM);
		return (errno);
	}
	path = getcwd(NULL, 0);
	if (!path)
		return (ENOMEM);
	envar = get_envar(cmd->mini->envars, "PWD");
	if (!envar && !set_envar(cmd->mini, "PWD", path, 0))
	{
		free(path);
		return (ENOMEM);
	}
	if (!replace_envar_value(envar, ft_strdup(path)))
		return (ENOMEM);
	free(path);
	return (0);
}
