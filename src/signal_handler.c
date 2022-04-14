/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handler.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 17:21:00 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/14 22:37:53 by jgalloni      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "custom_errors.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "readline/readline.h"
#include "signal_handling.h"
#include "structs.h"

void	hdoc_sig_parent(int sig)
{
	if (sig == SIGINT)
	{
		if (g_pid != -1)
			kill(g_pid, SIGTERM);
		g_pid = -1;
	}
}

void	sig_handler(int sig)
{
	if (sig == 137)
	{
		write(2, "\nOut of memory\n", 15);
		exit(ENOMEM);
	}
	else if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	exec_sig_handler(int sig)
{
	if (sig == SIGINT)
		printf("\n");
	else if (sig == SIGQUIT)
		printf("Quit: 3\n");
}
