#include "utils.h"
#include "builtins.h"
#include "errno.h"
#include <stdio.h>

int	mini_export(t_cmd *cmd)
{
	size_t	i;
	char	*dup;
	char	*equals_pos;

	if (char_array_len(cmd->params) < 2)
		return (mini_env(cmd));
	i = 1;
	while (cmd->params[i])
	{
		equals_pos = ft_strchr(cmd->params[i], '=');
		if (equals_pos == cmd->params[i])
		{
			printf("minishell: export: '%s': not a valid identifier\n",
				cmd->params[i]);
		}
		else if (equals_pos)
		{
			*equals_pos = '\0';
			if (ft_strschr(cmd->params[i], "${}"))
				printf("minishell: export: '%s': not a valid identifier\n",
					cmd->params[i]);
			else
				set_envar(cmd, cmd->params[i], equals_pos + 1);
		}
		i++;
	}
	return (0);
}
