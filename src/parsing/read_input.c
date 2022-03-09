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
#include "signal_handling.h"
#include "get_next_line.h"

void	handle_eof(char **line)
{
	char	*c;
	int		ret;

	c = ft_calloc(2, 1);
	get_next_line(0, NULL);
	while (1)
	{
		ret = read(0, c, 1);
		if (ret == -1)
			exit (errno);
		if (*c == '\n')
			break ;
		if (ret > 0)
			ret = join_realloc(line, c, 1);
		if (ret != 0)
			exit (ENOMEM);
	}
	free(c);
}

char	*readline_but_better(char *prompt, int fd)
{
	char	*line;
	char	*temp;
	int		ret;
	int		ret_2;

	temp = ".";
	ft_putstr_fd(prompt, 1);
	ret = get_next_line(0, &line);
	if (ret == -1)
		exit(ENOMEM);
	if (ret == 0 && !(line[0]))
		return (NULL);
	else if (ret == 0)
		handle_eof(&line);
	return (line);
}

void	input_to_fd(char *read_until, int fd)
{
	char	*in;
	int		ret;

	while (1)
	{
		in = readline("\001\e[1;40;31m\002>\001\e[0m\002 ");
		if (!in || (!read_until && in[0]))
			break ;
		ret = ft_strlen(in);
		if (ft_strncmp(in, read_until, ret) == 0 && ret > 0)
			break ;
		ret = ft_putstr_fd(in, fd);
		if (ret < 0)
			exit(errno);
		write(fd, "\n", 1);
		if (in)
			free(in);
	}
	if (in)
		free(in);
}

void	heredoc_child(t_cmd *cmd, char *delimiter, int fd[2])
{
	signal(SIGINT, SIG_IGN);
	close(fd[0]);
	input_to_fd(delimiter, fd[1]);
	close(fd[1]);
	//system("leaks minishell");
	exit(0);
}

int	read_from_child(char **dest, int fd, t_dlist *envars)
{
	int		ret;
	char	*buff;
	int		bytes;

	bytes = 1;
	if (g_pid == -1)
		return (0);
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
	ret = parse_envars(envars, dest);
	if (ret != 0)
		exit(ret);
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
		heredoc_child(cmd, delimiter, fd);
	g_pid = pid;
	signal(SIGINT, &hdoc_sig_parent);
	wait_n_processes(1, cmd->mini);
	if (cmd->mini->status == IGNORE)
		return (-3);
	close(fd[1]);
	ret = read_from_child(&(cmd->heredoc), fd[0], cmd->mini->envars);
	close(fd[0]);
	//printf("HEREDOC : %s:\n", cmd->heredoc);
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
		//free(in);
	}
	if (!in)
		return (PARSE_ERROR);
	ret = split_prompt(in, to, "|");
	//free (in);
	return (ret);
}
