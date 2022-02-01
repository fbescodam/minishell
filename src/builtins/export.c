#include "utils.h"
#include "builtins.h"
#include <errno.h>
#include "envars.h";
#include <stdio.h>

int	mini_export(t_cmd *cmd)
{
	size_t	i;
	char	*dup;
	char	*equals_pos;
	t_envar	*envar;

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
			if (ft_strschr(cmd->params[i], DISALLOWED_CHARS_IN_ENVAR_NAME))
				printf("minishell: export: '%s': not a valid identifier\n",
					cmd->params[i]);
			else
				set_envar(cmd, cmd->params[i], equals_pos + 1, 1);
		}
		else
		{
			envar = get_envar(cmd->mini->envars, cmd->params[i]);
			if (envar)
				envar->export = 1;
		}
		i++;
	}
	return (0);
}
