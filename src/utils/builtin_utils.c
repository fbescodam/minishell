#include "libft.h"
#include "structs.h"

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
	return (1);
}

static void	print_ptc_error(void *ptc_err)
{
	ft_putendl_fd((char *)ptc_err, 1);
}

void	print_ptc_errors(t_list *frake_err)
{
	if (!frake_err)
		return ;
	ft_lstiter(frake_err, &print_ptc_error);
}
