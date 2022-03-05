#include <stdlib.h>
#include <errno.h>
#include "utils.h"
#include "builtins.h"
#include "envars.h"

static void	export_err(char *id)
{
	print_builtin_err("export", id, "not a valid identifier");
}

int	mini_export(int is_child, t_cmd *cmd)
{
	size_t	i;
	char	*equals_pos;
	t_envar	*envar;

	if (char_array_len(cmd->params) < 2)
		return (mini_env(is_child, cmd));
	i = 1;
	while (cmd->params[i])
	{
		equals_pos = ft_strchr(cmd->params[i], '=');
		if (equals_pos == cmd->params[i] && is_child)
			export_err(cmd->params[i]);
		else if (equals_pos)
		{
			if (!is_valid_env_name(cmd->params[i]) && is_child)
				export_err(cmd->params[i]);
			else
			{
				*equals_pos = '\0';
				if (!set_envar(cmd->mini, cmd->params[i], equals_pos + 1, 1))
					return (ENOMEM);
			}
		}
		else
		{
			if (!is_valid_env_name(cmd->params[i]) && is_child)
				export_err(cmd->params[i]);
			envar = get_envar(cmd->mini->envars, cmd->params[i]);
			if (envar)
				envar->export = ft_str3join(envar->name, "=", envar->val);
			if (envar && !envar->export)
				return (ENOMEM);
		}
		i++;
	}
	return (0);
}
