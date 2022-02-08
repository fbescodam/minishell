#include <errno.h>
#include "utils.h"

// run in the parent,
int	mini_pwd(t_cmd *cmd)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (ENOMEM);
	if (!ptc_echo(cmd, path))
		return (ENOMEM);
	ft_free(path);
	return (0);
}
