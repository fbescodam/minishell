#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "utils.h"

// run in child, doesn't change memory.
int	mini_pwd(t_cmd *cmd)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (ENOMEM);
	printf("%s\n", path);
	ft_free(path);
	return (0);
}
