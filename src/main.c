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
		setup_signals();
		prompt = readline("\x1b[1mminishell> \x1b[0m");
		if (!prompt)
			force_exit(&mini, 0);
		//ret = parse_prompt(&mini, prompt);
		//if (ret != 0)
		//	error_manager(&mini, ret);
		parse_envars(mini.envars, &prompt);
		printf("prompt: \"%s\"\n", prompt);
		ft_free(prompt);
	}
}
