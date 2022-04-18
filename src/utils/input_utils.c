/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/08 23:54:40 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/18 17:02:34 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include "error_handling.h"
#include "execute.h"
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

static void	write_heredoc_inner(t_mini *mini, t_cmd *cmd, int pid, int fd[2])
{
	int	ret;

	if (pid == -1)
		force_exit(mini, errno);
	if (pid == 0)
	{
		close(fd[0]);
		ret = dup2(fd[1], 1);
		if (ret < 0)
			exit(errno);
		close(fd[1]);
		ret = ft_putstr_fd(cmd->heredoc, 1);
		if (ret < 0)
			exit(errno);
		exit (0);
	}
}

void	fork_read_child(char *delimiter, int read_nl, int fd[2])
{
	signal(SIGINT, SIG_IGN);
	close(fd[0]);
	input_to_fd(delimiter, fd[1], read_nl);
	close(fd[1]);
	exit(0);
}

void	write_heredoc(t_cmd *cmd, t_mini *mini)
{
	int	fd[2];
	int	pid;

	if (cmd->pipe_in[0])
	{
		close(cmd->pipe_in[0]);
		close(cmd->pipe_in[1]);
	}
	if (pipe(fd) < 0)
		force_exit(mini, errno);
	cmd->pipe_in[0] = fd[0];
	cmd->pipe_in[1] = fd[1];
	pid = fork();
	write_heredoc_inner(mini, cmd, pid, fd);
	wait_n_processes(1, mini);
}
