/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/26 23:45:39 by jgalloni      #+#    #+#                 */
/*   Updated: 2021/11/27 03:24:04 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "libft/libft.h"
#include <stdlib.h>
#include <signal.h>
#include "readline/readline.h"
#include "readline/history.h"
#include "utils.h"

static void	setup_signals(void)
{
	printf("setting up signals\n");
	signal(SIGTERM, exit_shell);
	signal(SIGHUP, exit_shell);
	signal(SIGINT, exit_shell);
	signal(SIGABRT, exit_shell);
	signal(SIGQUIT, exit_shell);
	signal(SIGTSTP, exit_shell);
}

int	parse_command(t_cmd *cmd, char *prompt)
{
	int	ret;

	printf("command: '%s'\n", prompt);
	if (!prompt)
		exit_shell_w_error(-1);
	cmd->params = ft_split(prompt, ' ');
	if (!cmd->params)
		exit_shell_w_error(ENOMEM);
	if (!cmd->params[0])
		return (0);
	if (ft_strncmp("exit", cmd->params[0], 5) == 0 && !cmd->params[1])
		exit_shell(-1);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	t_cmd	cmd;
	char	**paths;
	int		ret;
	char	buff[60];
	int		status;

	setup_signals();
	paths = set_path();
	while (1)
	{
		prompt = readline("minishell> ");
		ret = parse_command(&cmd, prompt);
		if (ret)
			execute_command(0, &cmd, paths);
		//free command list
	}
}
