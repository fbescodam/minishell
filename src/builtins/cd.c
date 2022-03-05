#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"
#include "envars.h"
#include "custom_errors.h"

// TODO: cd runs in the parent
int	mini_cd(int is_child, t_cmd *cmd)
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
			return (ENOENT);
		path = envar->val;
	}
	if (chdir(path) < 0)
		return (errno);
	if (is_child)
		return (0);
	path = getcwd(NULL, 0);
	if (!path)
		return (ENOMEM);
	envar = get_envar(cmd->mini->envars, "PWD");
	if (envar)
		ret = replace_envar_value(envar, path);
	else
		ret = set_envar(cmd->mini, "PWD", path, 0);
	free(path);
	if (!ret)
		return (ENOMEM);
	return (0);
}
