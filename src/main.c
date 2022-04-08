/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 17:21:02 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/08 22:41:23 by fbes          ########   odam.nl         */
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

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	int		ret;

	//rl_catch_signals = 0;
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
		add_history(mini.prompt);
		//printf("prompt after readline: \"%s\"\n", mini.prompt);
		ret = parse_set_envars_b4_comm(&mini, &mini.prompt);
		if (ret != 0)
			error_manager(&mini, ret);
		else
		{
			if (ret != 0)
				error_manager(&mini, ret);
			else
			{
				if (!set_mini_status(&mini, 0))
					error_manager(&mini, ENOMEM);
				//printf("prompt after parsing envars: \"%s\"\n", mini.prompt);
				ret = parse_prompt(&mini, mini.prompt);
				if (ret != 0)
					error_manager(&mini, ret);
				else
				{
					//print_command_list(mini.cmds);
					ret = execute_list(&mini);
				}
				//printf("prompt after parse_prompt: \"%s\"\n", mini.prompt);
			}
		}
		ft_free(mini.prompt);
		ft_lstclear(&(mini.cmds), &free_cmd);
		mini.prompt = NULL;
	}
}
