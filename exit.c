/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jgalloni <jgalloni@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/26 23:45:59 by jgalloni      #+#    #+#                 */
/*   Updated: 2021/12/06 20:27:38 by jgalloni      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "readline/readline.h"
#include "custom_errors.h"

/*
 * @brief Handle signals 
 * SIGINT is ctrl c
 * -1 is passed in case of EOF
 */

void	sig_handler(int sig)
{
	if (sig == 137)
	{
		write(2, "\nOut of memory\n", 15);
		exit(ENOMEM);
	}
	else if (sig == -1)
	{
		printf("Goodbye\n");
		exit(0);
	}
	else if (sig == SIGINT)
	{
		printf("\n"); // Move to a new line
    	rl_on_new_line(); // Regenerate the prompt on a newline
    	rl_replace_line("", 0); // Clear the previous text
    	rl_redisplay();
	}
}

/*
 * @brief Prints a custom or errno message and exits the process
 */

void	exit_shell_w_error(int err)
{
	if (err == -1)
	{
		printf(" exit\n");
		exit(errno);
	}
	if (err == CMDNF)
	{
		printf("minishell: command not found\n");
		exit (CMDNF);
	}
	perror("minishell");
	exit(errno);
}
