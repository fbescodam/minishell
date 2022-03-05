#include <stdio.h>
#include "readline/readline.h"
#include "readline/history.h"
#include "parse.h"
#include <stdlib.h>
#include "utils.h"
#include "custom_errors.h"
#include <signal.h>
#include "envars.h"
#include "execute.h"
#include <unistd.h>
#include "error_handling.h"

int	read_input(char *read_until, char **dest)
{
	char	*in;
	int		ret;

	if (*dest)
		free(*dest);
	*dest = ft_strdup("");
	while (1)
	{
		in = readline("\001\e[1;40;31m\002>\001\e[0m\002 ");
		if (!in || (!read_until && in[0]))
			break ;
		ret = ft_strlen(in);
		if (ft_strncmp(in, read_until, ret) == 0 && ret > 0)
			break ;
		in[ret] = '\n';
		ret = join_realloc(dest, in, ret + 1);
		if (ret != 0)
			return (-1);
		free(in);
	}
	return (0);
}

void	read_heredoc(t_cmd *cmd, char *delimiter, int fd[2])
{
	int		ret;
	
	ret = read_input(delimiter, &(cmd->heredoc));
	if (ret != 0)
		exit (ENOMEM);
	ret = parse_envars(cmd->mini->envars, &(cmd->heredoc));
	if (ret != 0)
		exit (ENOMEM);
	close(fd[0]);
	ret = ft_putstr_fd(cmd->heredoc, fd[1]);
	if (ret < 0)
		exit (errno);
	exit(0);
}

int	read_from_child(char **dest, int fd)
{
	int		ret;
	char	*buff;
	int		bytes;

	bytes = 1;
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
		free (buff);
	}
	return (0);
}

int	heredoc(t_cmd *cmd, char *delimiter)
{
	int		fd[2];
	int		ret;
	int		pid;

	if (cmd->heredoc)
		free(cmd->heredoc);
	cmd->heredoc = ft_strdup("");
	ret = pipe(fd);
	if (ret < 0)
		force_exit(cmd->mini, errno);
	pid = fork();
	if (pid == -1)
		force_exit(cmd->mini, errno);
	if (pid == 0)
		read_heredoc(cmd, delimiter, fd);
	close(fd[1]);
	wait_n_processes(1, cmd->mini);
	ret = read_from_child(&(cmd->heredoc), fd[0]);
	printf("HEREDOC : %s:\n", cmd->heredoc);
	return (0);
}

int	read_til_close_pipe(char ***to)
{
	char	*in;
	int		ret;

	ret = 0;
	while (1)
	{
		in = readline("\001\e[1;40;31m\002>\001\e[0m\002 ");
		if (!in || in[0])
			break;
		free(in);
	}
	if (!in)
		return (PARSE_ERROR);
	ret = split_prompt(in, to, "|");
	free (in);
	return (ret);
}
