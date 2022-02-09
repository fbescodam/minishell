#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "structs.h"
#include "error_handling.h"
#include "signal_handling.h"
#include "envars.h"

/**
  * @brief Assigns signal-handling functions to signals
  * SIGINT = Ctrl + C, interrupt process
  * SIGTERM = terminate software
  * SIGABRT = abort program
  * SIGQUIT = quit program
  * SIGTSTP = stop signal generated from keyboard
  */
void	setup_signals(t_mini *mini)
{
	if (signal(SIGTERM, sig_handler) == SIG_ERR ||
		signal(SIGABRT, sig_handler) == SIG_ERR ||
		signal(SIGQUIT, sig_handler) == SIG_ERR ||
		signal(SIGTSTP, sig_handler) == SIG_ERR ||
		signal(SIGINT, sig_handler) == SIG_ERR)
	{
		error_manager(mini, errno);
		force_exit(mini, errno);
	}
}

/**
 * @brief Export the envp variables into our environment variables list
 *
 * @param[in] mini The main struct
 * @param[in] envp The envp variables list
 * @return Returns 0 on error, 1 on success
 */
int	setup_envars(t_mini *mini, char **envp)
{
	size_t		i;
	char		*temp;
	char		*equals;
	int			ret;

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
		ret = set_envar(mini, temp, equals + 1, 1);
		free(temp);
		if (!ret)
			return (0);
		i++;
	}
	if (!mini->paths)
	{
		mini->paths = ft_split("", ':');
		if (!mini->paths)
			return (0);
	}
	if (!set_envar(mini, "?", "0", 0))
		return (0);
	temp = getcwd(NULL, 0);
	if (temp)
	{
		ret = set_envar(mini, "PWD", temp, 0);
		free(temp);
		if (!ret)
			return (0);
	}
	else
		return (0);
	return (1);
}

/**
 * @brief Set up the mini struct
 *
 * @param[in] mini The mini struct
 * @param[in] envp Envp
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
