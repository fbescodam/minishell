#include <fcntl.h>
#include <unistd.h>
#include "utils.h"
#include<sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>

int	input_redirect(int mode, t_cmd *cmd)
{
	int	fd;

	if (mode & IN_FILE)
		fd = open(cmd->in_file, O_RDONLY);
	else
		fd = cmd->in_fd;
	if (fd == -1)
		return (-1);
	dup2(fd, 0);
	close(fd);
	return (1);
}

int	output_redirect(int mode, t_cmd *cmd)
{
	int	fd;

	if (mode & OUT_FILE)
		fd = open(cmd->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		fd = cmd->out_fd;
	if (fd == -1)
		return (-1);
	dup2(fd, 1);
	close(fd);
	return (1);
}

int	fd_setup(int mode, t_cmd *cmd)
{
	int	ret;

	ret = 0;
	if ((mode & IN_FILE) || (mode & IN_FD))
		ret = input_redirect(mode, cmd);
	if (ret == -1)
		return (-1);
	if ((mode & OUT_FILE) || (mode & OUT_FD))
		ret = output_redirect(mode, cmd);
	if (ret == -1)
		return (-1);
	return (ret);
}

void	handler()
{
	printf("\n");
}

void	execute_command(int mode, t_cmd *cmd, char **paths)
{
	int		ret;
	int		pid;
	int		status;
	int		terminated_process;

	terminated_process = 0;
	ret = 0;
	cmd->path = check_command((cmd->params)[0], paths);
	pid = fork();
	signal(SIGINT, handler);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		ret = fd_setup(mode, cmd);
		if (ret == -1)
			exit_shell_w_error(0);
		execv(cmd->path, cmd->params);
		if (!cmd->path)
			exit_shell_w_error(127);
		exit_shell_w_error(0);
	}
	while (terminated_process != pid)
		terminated_process = wait(&status);
	if (((status) & 0x7f) == 0)
		errno = ((status) & 0xff00) >> 8;
}
