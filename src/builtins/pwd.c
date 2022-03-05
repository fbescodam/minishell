#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "utils.h"

// run in child, doesn't change memory.
int	mini_pwd(int is_child, t_cmd *cmd)
{
	char	*path;

	if (!is_child)
		return (0);
	path = getcwd(NULL, 0);
	if (!path)
		return (ENOMEM);
	printf("%s\n", path);
	ft_free(path);
	return (0);
}
