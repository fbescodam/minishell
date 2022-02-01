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
	char	*prompt;
	int		ret;

	setup_mini(&mini, envp);
	while (1)
	{
		setup_signals(&mini);
		prompt = readline("\001\x1b[1m\002minishell> \001\x1b[0m\002");
		if (!prompt)
			force_exit(&mini, 0);
		add_history(prompt);
		ret = parse_set_envars_b4_comm(&mini, &prompt);
		if (ret != 0)
			error_manager(&mini, ret);
		ret = parse_envars(mini.envars, &prompt);
		if (ret != 0)
			error_manager(&mini, ret);
		else
		{
			ret = parse_prompt(&mini, prompt);
			if (ret != 0)
				error_manager(&mini, ret);
			printf("prompt: \"%s\"\n", prompt);
		}
		ft_free(prompt);
	}
}
