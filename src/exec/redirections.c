/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jgalloni <jgalloni@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 15:43:06 by jgalloni      #+#    #+#                 */
/*   Updated: 2022/04/08 22:56:31 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
	if (token->fd != -1)
		fd_2 = token->fd;
	fd_1 = open((char *)(token->content), O_RDONLY);
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
	if (token->fd != -1)
		fd_2 = token->fd;
	if (token->flag == OUT_FILE)
		fd_1 = open((char *)(token->content), O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (token->flag == OUT_FILE_APPEND)
		fd_1 = open((char *)(token->content), O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd_1 == -1)
		return (-1);
	ret = dup2(fd_1, fd_2);
	if (ret < 0)
		return (-1);
	close(fd_1);
	return (0);
}
