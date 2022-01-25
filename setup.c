#include <signal.h>
#include <stdlib.h>
#include "structs.h"
#include "error_handling.h"
#include "signal_handling.h"

/**
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
	t_list	*current_env;

	mini->paths = get_path();
	if (!envp)
		return ;
	mini->envars = ft_lstnew(envp[0]);
	if (!(mini->envars))
		force_exit(mini, ENOMEM);
	i = 1;
	while (envp[i])
	{
		current_env = ft_lstnew(envp[i]);
		if (!current_env)
			force_exit(mini, ENOMEM);
		ft_lstadd_back(&(mini->envars), current_env);
		i++;
	}

}

void	setup_mini(t_mini *mini, char **envp)
{
	ft_bzero(mini, sizeof(t_mini));
	setup_envars(mini, envp);
}
