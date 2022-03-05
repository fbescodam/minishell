#include "libft.h"
#include "structs.h"

void	print_builtin_err(char *method, char *helping_hand, char *err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(method, 2);
	ft_putstr_fd(": ", 2);
	if (helping_hand)
	{
		ft_putstr_fd(helping_hand, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(err, 2);
}

t_cmd	*get_cmd_from_pid(t_list *cmds, int pid)
{
	t_list	*item;
	t_cmd	*cmd;

	item = cmds;
	while (item)
	{
		cmd = (t_cmd *)item->content;
		if (cmd->pid == pid)
			return (cmd);
		item = item->next;
	}
	return (NULL);
}
