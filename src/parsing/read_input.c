#include <stdio.h>
#include "readline/readline.h"
#include "readline/history.h"
#include "parse.h"
#include <stdlib.h>
#include "utils.h"

int	read_heredoc(t_cmd *cmd, char *content)
{
	char	*in;
	int		ret;

	if (cmd->heredoc)
		free(cmd->heredoc);
	cmd->heredoc = ft_strdup("");
	while (1)
	{
		in = readline("\001\e[1;40;31m\002>\001\e[0m\002 ");
		if (in)
		{
			ret = ft_strlen(in);
			if (in && ft_strncmp(in, content, ret) == 0 && ret > 0)
				break;
			in[ret] = '\n';
			ret = join_realloc(&(cmd->heredoc), in, ret + 1);
			if (ret != 0)
				return (-1);
			free(in);
		}
	}
	//expand variables in heredoc
	return (0);
}

int	read_til_close_pipe(char ***to)
{
	char	*in;
	int		ret;

	ret = 0;
	while (1)
	{
		in = readline("\001\e[1;40;31m\002>\001\e[0m\002 ");
		if (in && in[0])
			break;
		if (in)
			free(in);
	}
	ret = split_prompt(in, to, "|");
	free (in);
	return (ret);
}
