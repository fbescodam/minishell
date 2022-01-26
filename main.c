#include <stdio.h>
#include "setup.h"
#include "envars.h"
#include "debug.h"
#include "error_handling.h"
#include "readline/readline.h"
#include "readline/history.h"

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	char	*prompt;
	int		ret;

	setup_mini(&mini, envp);
	print_envars(&mini);
	while (1)
	{
		setup_signals();
		prompt = readline("\x1b[1mminishell> \x1b[0m");
		if (!prompt)
			force_exit(&mini, 0);
		printf("PROMPT : \"%s\"\n", prompt);
		parse_envars(mini.envars, &prompt);
		printf("PARSED PROMPT : \"%s\"\n", prompt);
		ft_free(prompt);
	}
}
