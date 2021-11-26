#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "libft/libft.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "utils.h"


void	stop_server(int sig)
{
 	if (sig == 137)
	{
		write(2, "\nOut of memory\n", 9);
		exit (12);
	}
}

static void	setup_signals()
{
	signal(SIGTERM, stop_server);
	signal(SIGHUP, stop_server);
	signal(SIGINT, stop_server);
	signal(SIGABRT, stop_server);
	signal(SIGQUIT, stop_server);
	signal(SIGTSTP, stop_server);
}

int	parse_command(t_cmd *cmd, char *prompt)
{
	int	ret;
	
	if (!prompt)
		error_exit(-1);
	cmd->params = ft_split(prompt, ' ');
	if (!cmd->params)
		stop_server(12);
	if (!cmd->params[0])
		return (0);
	if (ft_strncmp("exit", cmd->params[0], 5) == 0 && !cmd->params[1])
		exit(0);
	return (1);
}

int main()
{
	char	*prompt;
	t_cmd	cmd;
	char	**paths;
	int		ret;
	char buff[60];

	setup_signals();
	paths = set_path();
	while (1)
	{
		prompt = readline(">minishell ");
		ret = parse_command(&cmd, prompt);
		
		if (ret)
			execute_command(0, &cmd, paths);
		//char *cwd = getcwd(buff, 60);
		//printf("%s\n", cwd);
		//free command list
	}
}
