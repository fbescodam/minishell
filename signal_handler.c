/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handler.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jgalloni <jgalloni@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/26 23:45:59 by jgalloni      #+#    #+#                 */
/*   Updated: 2022/01/23 18:00:19 by jgalloni      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "readline/readline.h"
#include "custom_errors.h"
#include "utils.h"

/**
  * @brief Handle signals
  * SIGINT is ctrl c
  * -1 is passed in case of EOF
  */

void	sig_handler(int sig)
{
	// system("leaks minishell");
	if (sig == 137)
	{
		write(2, "\nOut of memory\n", 15);
		exit(ENOMEM);
	}
	else if (sig == SIGINT)
	{
		printf("\n"); // Move to a new line
		rl_replace_line("", 0); // Clear the previous text
		printf("\x1b[1A\033[11C\x1b[0K\n");
		// Hooray for ANSI Escape Sequences!
		// \x1b stands for the ESCAPE key, then [1A goes up one line ([2A would go up two lines)
		// then [12C moves the cursor 12 places to the right
		// [0K removes all character from that position til the end of the line in the terminal
		rl_on_new_line(); // Regenerate the prompt on a newline
		rl_redisplay();
	}
}

void	error_handler(t_cmd *cmd, int err)
{
	if (err == PARSE_ERROR)
	{
		printf("minishell : syntax error\n");
		errno = PARSE_ERROR;
	}
	else
		exit_shell_w_error(cmd, err);
}

/**
  * @brief Prints a custom or errno message and exits the process
  * @param err An error code. If set to -2, nothing is printed.
  */


void	exit_shell_w_error(t_cmd *cmd, int err)
{
	if (cmd)			//@Freek free the whole list of cmds instead of one!
	{
		free_mini(cmd->mini);
		free_cmd(cmd);
	}
	// system("leaks minishell");
	if (err == -1)
	{
		// exit normally, printing exit
		printf("\x1b[1A\033[11Cexit\n");
		rl_replace_line("exit", 1);
		exit(errno);
	}
	else if (err == -2)
	{
		// exit normally but without printing exit
		exit(errno);
	}
	else if (err == CMDNF)
	{
		// ONLY RUN IN CHILD
		printf("minishell: command not found\n");
		exit(CMDNF);
	}
	else if (err < 0)
	{
		printf("minishell: an error occurred (code %d)\n", err);
		exit(1);
	}
	else if (err < -255)
	{
		printf("minishell: a major error occurred (code %d)\n", err);
		exit(2);
	}
	else
	{
		perror("minishell");
		exit(err);
	}
}
