#include "structs.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int	input_redirect(t_token *token)
{
	int	fd_1;
	int	fd_2;
	int	ret;

	fd_2 = 0;
	if (token->fd != -1 && token->flag != PIPE_IN)
		fd_2 = token->fd;
	if (token->flag != PIPE_IN)
		fd_1 = open((char *)(token->content), O_RDONLY);
	else
		fd_1 = ((int*)(token->content))[0];
	if (fd_1 == -1)
		return (-1);
	ret = dup2(fd_1, fd_2);
	if (ret < 0)
		return (-1);
	close(fd_1);
	return (0);
}

int	output_redirect(t_token *token)
{
	int	fd_1;
	int	fd_2;
	int	ret;

	fd_2 = 1;
	if (token->fd != -1 && token->flag != PIPE_OUT)
		fd_2 = token->fd;
	if (token->flag != PIPE_OUT)
		fd_1 = open((char *)(token->content), O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		fd_1 = ((int*)(token->content))[1];
	printf("FLAG : %d, fd_1 : %d\n", token->flag, fd_1);
	if (fd_1 == -1)
		return (-1);
	ret = dup2(fd_1, fd_2);
	if (ret < 0)
		return (-1);
	close(fd_1);
	return (0);
}
