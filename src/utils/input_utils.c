/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/08 23:54:40 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/08 23:58:49 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include "readline/readline.h"
#include "readline/history.h"

static void	input_to_fd(char *read_until, int fd, int write_nl)
{
	char	*in;
	int		ret;

	while (1)
	{
		in = readline("\001\e[1;40;31m\002>\001\e[0m\002 ");
		if (!in)
			break ;
		if (!read_until && in[0])
		{
			ft_putstr_fd(in, fd);
			break ;
		}
		ret = ft_strlen(in);
		if (ret > 0 && ft_strncmp(in, read_until, ret) == 0)
			break ;
		ret = ft_putstr_fd(in, fd);
		if (ret < 0)
			exit(errno);
		if (write_nl)
			write(fd, "\n", 1);
		ft_free(in);
	}
	ft_free(in);
}

void	fork_read_child(char *delimiter, int read_nl, int fd[2])
{
	signal(SIGINT, SIG_IGN);
	close(fd[0]);
	input_to_fd(delimiter, fd[1], read_nl);
	close(fd[1]);
	exit(0);
}
