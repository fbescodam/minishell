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

void	input_to_fd(char *read_until, int fd, int write_nl)
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
			break;
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
	system("leaks minishell");
	signal(SIGINT, SIG_IGN);
	close(fd[0]);
	input_to_fd(delimiter, fd[1], read_nl);
	close(fd[1]);
	exit(0);
}

int	read_from_child(char **dest, int fd, t_dlist *envars)
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
		free (buff);
	}
	if (envars)
		ret = parse_envars(envars, dest);
	if (ret != 0)
		return(ret);
	return (0);
}

int	fork_read_input(t_mini *mini, char *delimiter, int read_nl, char **dest)
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
	wait_n_processes(1, mini);
	close(fd[1]);
	if (g_pid != -1 && read_nl)
		ret = read_from_child(dest, fd[0], mini->envars);
	else if (g_pid != -1)
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
		force_exit(cmd->mini, ret);
	ret = fork_read_input(cmd->mini, delimiter, 1, &(cmd->heredoc));
	if (ret == IGNORE)
		return (-3);
	if (ret != 0)
		force_exit(cmd->mini, ret);
	return (0);
}

int	read_til_close_pipe(char ***to, t_mini *mini)
{
	char	*in;
	int		ret;

	in = ft_strdup ("");
	if (!in)
		return (ENOMEM);
	ret = fork_read_input(mini, NULL, 0, &in);
	if (ret == IGNORE)
	{
		ft_free(in);
		return (IGNORE);
	}
	if (ret != 0)
		force_exit(mini, ret);
	ret = add_string_to_array(to, in);
	if (ret != 0)
		force_exit(mini, ret);
	if (in && in[0] == '\0')
		return(PARSE_ERROR);
	return (0);
}
