#include "utils.h"
#include "envars.h"
#include "libft.h"

// run in the parent, no text is ever displayed
// TODO: use previous and next
int	mini_unset(t_cmd *cmd)
{
	size_t	i;
	t_ditem	*to_unset;

	if (char_array_len(cmd->params) < 2)
		return (0);
	i = 1;
	while (cmd->params[i])
	{
		to_unset = get_envar_item(cmd->mini->envars, cmd->params[i]);
		if (to_unset)
			ft_dlstrem(cmd->mini->envars, to_unset, &free_envar);
		i++;
	}
	return (0);
}
