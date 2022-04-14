/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jgalloni <jgalloni@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/03 16:40:43 by jgalloni      #+#    #+#                 */
/*   Updated: 2022/04/14 23:28:54 by jgalloni      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "parse.h"
#include "utils.h"
#include "custom_errors.h"
#include "envars.h"
#include "execute.h"
#include "error_handling.h"
#include "signal_handling.h"
#include "get_next_line.h"

static int	read_from_child(char **dest, int fd, t_dlist *envars)
{
	int		ret;
	char	*buff;
	int		bytes;

	bytes = 1;
	ret = 0;
	while (bytes)
	{
		buff = (char *)ft_calloc(50, 1);
		if (!buff)
			return (ENOMEM);
		bytes = read(fd, buff, sizeof(buff));
		if (bytes == -1)
			return (errno);
		ret = join_realloc(dest, buff, bytes);
		if (ret < 0)
			return (ENOMEM);
		free(buff);
	}
	if (envars)
		ret = parse_envars(envars, dest);
	return (ret);
}

static int	fork_read_input(t_mini *mini, char *delimiter,
		int read_nl, char **dest)
{
	int	ret;
	int	pid;
	int	fd[2];

	ret = pipe(fd);
	if (ret < 0)
		force_exit(mini, errno);
	pid = fork();
	if (pid == -1)
		force_exit(mini, errno);
	if (pid == 0)
		fork_read_child(delimiter, read_nl, fd);
	g_pid = pid;
	signal(SIGINT, &hdoc_sig_parent);
	signal(SIGQUIT, &hdoc_sig_parent);
	wait_n_processes(1, mini);
	close(fd[1]);
	if (g_pid != -1 && read_nl)
		ret = read_from_child(dest, fd[0], mini->envars);
	else if (g_pid != -1 && !read_nl)
		ret = read_from_child(dest, fd[0], NULL);
	close(fd[0]);
	if (g_pid == -1)
		return (IGNORE);
	return (ret);
}

int	heredoc(t_cmd *cmd, char *delimiter)
{
	int		ret;

	if (cmd->heredoc)
		free(cmd->heredoc);
	cmd->heredoc = ft_strdup("");
	if (!cmd->heredoc)
		force_exit(cmd->mini, ENOMEM);
	ret = fork_read_input(cmd->mini, delimiter, 1, &(cmd->heredoc));
	if (ret == IGNORE)
		return (-3);
	if (ret == PARSE_ERROR)
		return (-2);
	if (ret != 0)
		force_exit(cmd->mini, ret);
	return (0);
}
