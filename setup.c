#include "include/structs.h"
#include "include/error_handling.h"
#include "include/signal_handling.h"

/*
 * @brief Assigns signal-handling functions to signals
 */

void	setup_signals(void)
{
	signal(SIGTERM, sig_handler);
	signal(SIGHUP, sig_handler);
	signal(SIGINT, sig_handler);
	signal(SIGABRT, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGTSTP, sig_handler);
}

char	**get_path(void)
{
	char	*env;
	char	**paths;

	env = getenv("PATH");
	if (!env)
		env = ft_calloc(1, sizeof(char));
	if (!env)
		force_exit(NULL, ENOMEM);
	paths = ft_split(env, ':');
	if (!paths)
		force_exit(NULL, ENOMEM);
	return (paths);
}

void	setup_envars(t_mini *mini, char **envp)	//*set_envar(t_cmd *cmd, char *name, char *val)
{
	int		i;
	char	*envar_value_pos;

	mini->paths = get_path();
	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		envar_value_pos = ft_strchr(envp[i], ':');
		*envar_value_pos = '\0';
		envar_value_pos = envar_value_pos + 1;
		//set_envar(mini, envp[i], envar_value_pos);
		i++;
	}
	
}

void	setup_mini(t_mini *mini, char **envp)
{
	ft_bzero(mini, sizeof(t_mini));
	//setup_envars(mini, envp);
}
