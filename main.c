/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jgalloni <jgalloni@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/26 23:45:39 by jgalloni      #+#    #+#                 */
/*   Updated: 2022/01/19 22:24:48 by jgalloni      ########   odam.nl         */
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
 * handed on to execution
 */

int	parse_command(t_list *cmds, char *prompt)
{
	int	ret;

	ret = tokenize(prompt, &cmds);
	if (ret == PARSE_ERROR)
	{
		printf("minishell: syntax error\n");
		errno = PARSE_ERROR;
		return (0);
	}
	if (ret != 0)
		exit_shell_w_error(ret);
	if (!(((t_cmd *)(cmds->content))->tokens))
		return (0);
	return (1);
}

int	setup_cmds(t_list **cmds)
{
	t_cmd *cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return(ENOMEM);
	*cmds = ft_lstnew(cmd);
	if (!cmds)
		return(ENOMEM);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	char	**prompts;
	t_list	*cmds; // this should become a t_list of cmds at some point
	char	**paths;
	int		ret;
	size_t	i;

	//treat exit as a command

	paths = set_path();
	ret = setup_cmds(&cmds);
	if (ret != 0)
		exit_shell_w_error(ret);
	while (1)
	{
		setup_signals();
		prompt = readline("\x1b[1mminishell> \x1b[0m");
		if (!prompt)
			exit_shell_w_error(-1);
		else
		{
			if (prompt && *prompt)
			{
				prompts = ft_split(prompt, ';');
				i = 0;
				while (prompts[i])
				{
					ret = parse_command(cmds, prompts[i]);
					if (ret)
						execute_command((t_cmd*)(cmds->content), paths);
					i++;
				}
				ft_free_double_ptr((void **)prompts);
				add_history(prompt);
			}
			//free command and token lists
			ft_free(prompt);
		}
	}
	ft_free(cmds);
}
