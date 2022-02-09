#include "utils.h"
#include "builtins.h"

/**
 * @brief Check if given command is a reserved keyword for minishell and if it
 * is, run it.
 * @param[in] cmd Command struct
 * @return Returns -1 if no reserved keyword, 0 if it was and it completed
 * successfully, > 0 on system error (using errno), < 0 on minishell error
 */
int	check_run_reserved_cmds(t_cmd *cmd, int which)
{
	if (which == MINI_BUILTIN_CD)
		return (mini_cd(cmd));
	if (which == MINI_BUILTIN_EXIT)
		return (mini_exit(cmd));
	if (which == MINI_BUILTIN_PWD)
		return (mini_pwd(cmd));
	if (which == MINI_BUILTIN_ECHO)
		return (mini_echo(cmd));
	if (which == MINI_BUILTIN_EXPORT)
		return (mini_export(cmd));
	if (which == MINI_BUILTIN_ENV)
		return (mini_env(cmd));
	if (which == MINI_BUILTIN_UNSET)
		return (mini_unset(cmd));
	return (-1);
}

/**
 * @brief Check if a command is a reserved command (builtin in minishell)
 * @param[in] cmd Command struct
 * @return Returns an integer corresponding to the builtin command (builtin.h)
 */
int	is_reserved(t_cmd *cmd)
{
	if (ft_strncmp("cd\0", cmd->params[0], 3) == 0)
		return (MINI_BUILTIN_CD);
	if (ft_strncmp("exit\0", cmd->params[0], 5) == 0)
		return (MINI_BUILTIN_EXIT);
	if (ft_strncmp("pwd\0", cmd->params[0], 4) == 0)
		return (MINI_BUILTIN_PWD);
	if (ft_strncmp("echo\0", cmd->params[0], 5) == 0)
		return (MINI_BUILTIN_ECHO);
	if (ft_strncmp("export\0", cmd->params[0], 7) == 0)
		return (MINI_BUILTIN_EXPORT);
	if (ft_strncmp("env\0", cmd->params[0], 4) == 0)
		return (MINI_BUILTIN_ENV);
	if (ft_strncmp("unset\0", cmd->params[0], 6) == 0)
		return (MINI_BUILTIN_UNSET);
	return (MINI_BUILTIN_NONE);
}

/**
 * @brief Check if a builtin command is supposed to be run in a child
 * @param[in] which The builtin command's ID from the list in builtin.h
 * @return Returns 1 on true, 0 on false
 */
int	run_in_child(int which)
{
	if (which == MINI_BUILTIN_ECHO || which == MINI_BUILTIN_ENV
		|| which == MINI_BUILTIN_PWD)
		return (1);
	return (0);
}
