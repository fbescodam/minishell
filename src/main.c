/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 17:21:02 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/18 21:02:39 by jgalloni      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"
#include "envars.h"
#include "debug.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "error_handling.h"
#include "readline/readline.h"
#include "readline/history.h"
#include "parse.h"
#include "utils.h"
#include "execute.h"

static void	after_rl(t_mini *mini)
{
	int		ret;

	ret = parse_set_envars_b4_comm(mini, &mini->prompt);
	if (ret != 0)
		error_manager(mini, ret);
	else
	{
		ret = parse_envars(mini->envars, &mini->prompt);
		if (ret != 0)
			error_manager(mini, ret);
		else
		{
			if (!set_mini_status(mini, 0))
				error_manager(mini, ENOMEM);
			ret = parse_prompt(mini, mini->prompt);
			if (ret != 0)
				error_manager(mini, ret);
			else
			{
				ret = execute_list(mini);
				if (ret != 0)
					error_manager(mini, ret);
			}
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	argc = 3;
	if (!setup_mini(&mini, argv[0], envp))
		force_exit(&mini, 1);
	while (1)
	{
		setup_signals(&mini);
		mini.cmds = NULL;
		mini.prompt = readline(KUT);
		if (!mini.prompt)
		{
			printf("\x1b[1A\033[10C exit\n");
			rl_replace_line(" exit", 1);
			force_exit(&mini, 0);
		}
		if (!replace_tabs(&mini.prompt))
			force_exit(&mini, ENOMEM);
		if (mini.prompt && mini.prompt[0])
			add_history(mini.prompt);
		after_rl(&mini);
		ft_free(mini.prompt);
		ft_lstclear(&(mini.cmds), &free_cmd);
		mini.prompt = NULL;
	}
}
