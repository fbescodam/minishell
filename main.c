/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jgalloni <jgalloni@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/26 23:45:39 by jgalloni      #+#    #+#                 */
/*   Updated: 2021/12/06 21:36:19 by jgalloni      ########   odam.nl         */
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
#include "custom_errors.h"

/*
 * @brief Assigns signal-handling functions to signals
 */

static void	setup_signals(void)
{
	signal(SIGTERM, sig_handler);
	signal(SIGHUP, sig_handler);
	signal(SIGINT, sig_handler);
	signal(SIGABRT, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGTSTP, sig_handler);
}

/*
 * @brief Parses the user's prompt into a list of tokens
 * prompt is null on EOF signal
 * @return : 0 when nothing should be executed, 1 when parsed tokens can be
 * ended on to execution
 */

int	parse_command(t_cmd *cmd, char *prompt)
{
	int	ret;

	if (!prompt)
		exit_shell_w_error(-1); //EOF
	ret = tokenize(prompt, &(cmd->tokens));
	if (ret == PARSE_ERROR)
	{
		printf("minishell: syntax error\n");
		errno = PARSE_ERROR;
		return (0);
	}
	if (ret != 0)
		exit_shell_w_error(ret);
	if (!(cmd->tokens))
		return (0);
	return (1);
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

	//treat exit as a command 
	
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
