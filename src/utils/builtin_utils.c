#include "libft.h"
#include "structs.h"

int	ptc_echo(t_cmd *cmd, char *str)
{
	char	*temp;
	t_list	*item;

	temp = ft_strdup(str);
	if (!temp)
		return (0);
	item = ft_lstnew(temp);
	if (!item)
		return (0);
	ft_lstadd_back(&cmd->frake_out, item);
}

int	ptc_error(t_cmd *cmd, char *str)
{
	char	*temp;
	t_list	*item;

	temp = ft_strdup(str);
	if (!temp)
		return (0);
	item = ft_lstnew(temp);
	if (!item)
		return (0);
	ft_lstadd_back(&cmd->frake_err, item);
}
