/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jgalloni <jgalloni@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/26 23:45:39 by jgalloni      #+#    #+#                 */
/*   Updated: 2021/12/05 18:56:52 by jgalloni      ########   odam.nl         */
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
#include "tokens.h"

static void	setup_signals(void)
{
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

	if (!prompt)
		exit_shell_w_error(-1);
	ret = tokenize(prompt, &(cmd->tokens));
	if (ret == -1)
		exit_shell_w_error(ENOMEM);
	if (!(cmd->tokens))
		return (0);
	//ret = setup_cmd(cmd, *tokens);
	//if (ret == -1)
	//	exit_shell_w_error(ENOMEM);
	return (ret);
}



int	main(int argc, char **argv, char **envp)
{
	t_list *tokens;
	char	*prompt;
	t_cmd	*cmd; // this should become a t_list of cmds at some point
	char	**paths;
	int		ret;
	char	buff[60];
	int		status;

	//treat exit as a command ?
	
	paths = set_path();
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	while (1)
	{
		setup_signals();
		prompt = readline("minishell> ");
		
		ret = parse_command(cmd, prompt);
		if (ret)
			execute_command(cmd, paths);
		//free command and token lists
	}
}
