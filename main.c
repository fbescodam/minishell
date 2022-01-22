/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jgalloni <jgalloni@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/26 23:45:39 by jgalloni      #+#    #+#                 */
/*   Updated: 2022/01/22 19:42:48 by jgalloni      ########   odam.nl         */
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
#include "parse.h"

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
 * handed on to execution
 */

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	char	*prompt;
	t_list	*cmds;
	int		ret;
	size_t	i;

	ft_bzero(&mini, sizeof(t_mini));
	mini.paths = get_path();
	while (1)
	{
		setup_signals();
		prompt = readline("\x1b[1mminishell> \x1b[0m");
		if (!prompt)
			exit_shell_w_error(NULL, -1);
		else
			parse_prompt(prompt, cmds, &mini);
	}
	ft_lstclear(&cmds, &free_cmd); //how does the program evnen ever get here
	free_mini(&mini);
}
