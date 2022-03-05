#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include "structs.h"
#include "error_handling.h"
#include "signal_handling.h"
#include "envars.h"
	#	include <stdio.h>

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
	if (signal(SIGTERM, sig_handler) == SIG_ERR
		|| signal(SIGABRT, sig_handler) == SIG_ERR
		|| signal(SIGQUIT, sig_handler) == SIG_ERR
		|| signal(SIGTSTP, sig_handler) == SIG_ERR
		|| signal(SIGINT, sig_handler) == SIG_ERR)
	{
		error_manager(mini, errno);
		force_exit(mini, errno);
	}
}

static int	setup_reserved_envars(t_mini *mini, char *shellname)
{
	char	*path;
	int		ret;

	if (!set_envar(mini, "?", "0", 0))
		return (0);
	if (!set_envar(mini, "#", "0", 0))
		return (0);
	if (!set_envar(mini, "0", shellname, 0))
		return (0);
	path = getcwd(NULL, 0);
	if (path)
	{
		ret = set_envar(mini, "PWD", path, 0);
		free(path);
		if (!ret)
			return (0);
	}
	else
		return (0);
	return (1);
}

/**
 * @brief Export the envp variables into our environment variables list
 *
 * @param[in] mini The main struct
 * @param[in] envp The envp variables list
 * @return Returns 0 on error, 1 on success
 */
static int	setup_envars(t_mini *mini, char *shellname, char **envp)
{
	char		**envp_temp;
	char		*temp;
	char		*equals;
	int			ret;

	if (!envp)
		return (1);
	envp_temp = envp;
	while (*envp_temp)
	{
		if (ft_strchr(RESERVED_ENVAR_NAMES, (*envp_temp)[0]) && (*envp_temp)[1] == '=')
		{
			envp_temp++;
			continue ;
		}
		temp = ft_strdup(*envp_temp);
		if (!temp)
			return (0);
		equals = ft_strchr(temp, '=');
		*equals = '\0';
		ret = set_envar(mini, temp, equals + 1, 1);
		free(temp);
		if (!ret)
			return (0);
		envp_temp++;
	}
	if (!mini->paths)
	{
		mini->paths = ft_split("", ':');
		if (!mini->paths)
			return (0);
	}
	return (setup_reserved_envars(mini, shellname));
}

/**
 * @brief Set up the mini struct and termios stuff
 *
 * @param[in] mini The mini struct
 * @param[in] envp Envp
 * @return Returns 0 on error, 1 on success
 */
int	setup_mini(t_mini *mini, char *shellname, char **envp)
{
	struct termios	raw;
	char			*temp;

	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	ft_bzero(mini, sizeof(t_mini));
	mini->envars = ft_dlstnew();
	if (!mini->envars)
		return (0);
	if (!setup_envars(mini, shellname, envp))
		return (0);
	return (1);
}
