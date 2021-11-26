/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jgalloni <jgalloni@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/26 23:45:59 by jgalloni      #+#    #+#                 */
/*   Updated: 2021/11/26 23:48:00 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

void	exit_shell(int sig)
{
	if (sig == 137)
	{
		write(2, "\nOut of memory\n", 15);
		exit(ENOMEM);
	}
	else
	{
		printf("Goodbye\n");
		exit(0);
	}
}

void	exit_shell_w_error(int err)
{
	if (err == -1)
	{
		printf(" exit\n");
		exit(errno);
	}
	if (err == 127)
		errno = 127;
	perror("minishell");
	exit(errno);
}
