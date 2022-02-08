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

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	int		ret;

	if (!setup_mini(&mini, envp))
		force_exit(&mini, 1);
	while (1)
	{
		setup_signals(&mini);
		mini.prompt = readline(KUT);
		if (!mini.prompt)
		{
			printf("\x1b[1A\033[10Cexit\n");
			rl_replace_line("exit", 1);
			force_exit(&mini, 0);
		}
		add_history(mini.prompt);
		printf("prompt after readline: \"%s\"\n", mini.prompt);
		ret = parse_set_envars_b4_comm(&mini, &mini.prompt);
		if (ret != 0)
			error_manager(&mini, ret);
		else
		{
			printf("prompt after parsing envars to set: \"%s\"\n", mini.prompt);
			ret = parse_envars(mini.envars, &mini.prompt);
			if (ret != 0)
				error_manager(&mini, ret);
			else
			{
				printf("prompt after parsing envars: \"%s\"\n", mini.prompt);
				ret = parse_prompt(&mini, mini.prompt);
				if (ret != 0)
					error_manager(&mini, ret);
				printf("prompt after parse_prompt: \"%s\"\n", mini.prompt);
			}
		}
		ft_free(mini.prompt);
		mini.prompt = NULL;
	}
}
