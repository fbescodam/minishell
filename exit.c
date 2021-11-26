#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void	error_exit(int err)
{
	if (err == -1)
	{
		printf(" exit\n");
		exit (errno);
	}
	if (err == 127)
		errno = 127;
	perror("minishell");
	exit (errno);
}
