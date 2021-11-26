#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void	error_exit(int err)
{
	if (err == 127)
		errno = 127;
	perror("minishell");
	exit (errno);
}
