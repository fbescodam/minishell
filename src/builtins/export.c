#include <stdlib.h>
#include <errno.h>
#include "utils.h"
#include "builtins.h"
#include "envars.h"

static int	export_error(t_cmd *cmd, char *str)
{
	char	*temp;

	temp = ft_strreplace("minishell: export: @: not a valid identifier",
			"@", str);
	if (!temp)
		return (0);
	if (!ptc_error(cmd, temp))
	{
		free(temp);
		return (0);
	}
	free(temp);
	return (1);
}

// export runs in the parent, sends error messages to the child.
int	mini_export(t_cmd *cmd)
{
	size_t	i;
	char	*equals_pos;
	t_envar	*envar;

	if (char_array_len(cmd->params) < 2)
		return (mini_env(cmd));
	i = 1;
	while (cmd->params[i])
	{
		equals_pos = ft_strchr(cmd->params[i], '=');
		if (equals_pos == cmd->params[i] && !export_error(cmd, cmd->params[i]))
			return (ENOMEM);
		else if (equals_pos)
		{
			if (!is_valid_env_name(cmd->params[i])
				&& !export_error(cmd, cmd->params[i]))
				return (ENOMEM);
			else
			{
				*equals_pos = '\0';
				set_envar(cmd->mini, cmd->params[i], equals_pos + 1, 1);
			}
		}
		else
		{
			if (!is_valid_env_name(cmd->params[i])
				&& !export_error(cmd, cmd->params[i]))
				return (ENOMEM);
			envar = get_envar(cmd->mini->envars, cmd->params[i]);
			if (envar)
				envar->export = 1;
		}
		i++;
	}
	return (0);
}
