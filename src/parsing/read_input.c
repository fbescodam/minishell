#include <stdio.h>
#include "readline/readline.h"
#include "readline/history.h"
#include "parse.h"
#include <stdlib.h>

int	read_til_close_pipe(char ***to)
{
	char	*in;
	int		ret;

	ret = 0;
	while (1)
	{
		in = readline("\001\e[1;40;31m\002>\001\e[0m\e[7;40;31m\002open_pipe\001\e[0m\e[1m\002> \001\e[0m\002");
		if (in[0])
			break;
		free(in);
	}
	ret = split_prompt(in, to, "|");
	return (ret);
}
