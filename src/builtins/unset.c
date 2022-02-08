#include "utils.h"
#include "libft.h"

// run in the parent, no text is ever displayed
int	mini_unset(t_cmd *cmd)
{
	size_t	i;
	int		index;
	t_list	*to_unset;
	t_list	*previous;

	if (char_array_len(cmd->params) < 2)
		return (0);
	i = 1;
	while (cmd->params[i])
	{
		index = get_envar_as_list(&to_unset, cmd->mini->envars, cmd->params[i]);
		if (index > -1)
		{
			if (index > 0)
			{
				previous = ft_lstget(cmd->mini->envars, index - 1);
				previous->next = to_unset->next;
			}
			else
				cmd->mini->envars = to_unset->next;
			ft_lstdelone(to_unset, &free_envar);
		}
		i++;
	}
	return (0);
}
