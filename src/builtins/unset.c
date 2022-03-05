#include "utils.h"
#include "envars.h"
#include "libft.h"

int	mini_unset(int is_child, t_cmd *cmd)
{
	size_t	i;
	t_ditem	*to_unset;

	if (char_array_len(cmd->params) < 2)
		return (0);
	i = 1;
	while (cmd->params[i])
	{
		if (!is_valid_env_name(cmd->params[i]) && is_child)
			print_builtin_err("export", cmd->params[i],
				"not a valid identifier");
		else
		{
			to_unset = get_envar_item(cmd->mini->envars, cmd->params[i]);
			if (to_unset)
				ft_dlstrem(cmd->mini->envars, to_unset, &free_envar);
		}
		i++;
	}
	return (0);
}
