#include <signal.h>
#include <stdlib.h>
#include "structs.h"
#include "error_handling.h"
#include "signal_handling.h"
#include "envars.h"

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

/**
 * @brief Get the system PATH variable
 */
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

/**
 * @brief Export the envp variables into our environment variables list
 *
 * @param mini The main struct
 * @param envp The envp variables list
 * @return Returns 0 on error, 1 on success
 */
int	setup_envars(t_mini *mini, char **envp)
{
	size_t		i;
	char		*temp;
	char		*equals;

	mini->paths = get_path();
	if (!envp)
		return (1);
	i = 1;
	while (envp[i])
	{
		temp = ft_strdup(envp[i]);
		if (!temp)
			return (0);
		equals = ft_strchr(temp, '=');
		*equals = '\0';
		set_envar(mini->envars, temp, equals + 1);
		free(temp);
		i++;
	}
	return (1);
}

/**
 * @brief Set up the mini struct
 *
 * @param mini The mini struct
 * @param envp Envp
 * @return Returns 0 on error, 1 on success
 */
int	setup_mini(t_mini *mini, char **envp)
{
	ft_bzero(mini, sizeof(t_mini));
	mini->envars = ft_dlstnew();
	if (!mini->envars)
		return (0);
	if (!setup_envars(mini, envp))
		return (0);
	return (1);
}
