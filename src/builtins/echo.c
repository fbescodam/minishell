#include "libft.h"
#include "utils.h"

// TODO: echo DOES always run in the child! It doesn't change any memory.
int	mini_echo(t_cmd *cmd)
{
	size_t	i;
	char	add_nl;
	char	*temp;

	add_nl = 1;
	i = 1;
	while (cmd->params[i] && ft_strncmp("-n\0", cmd->params[i], 3) == 0)
	{
		add_nl = 0;
		i++;
	}
	while (cmd->params[i])
	{
		ft_putstr_fd(cmd->params[i], 1);
		if (cmd->params[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (add_nl)
		ft_putchar_fd('\n', 1);
	return (0);
}
