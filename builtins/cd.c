/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/19 22:47:09 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/23 18:00:47 by jgalloni      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.h"
#include "../custom_errors.h"
#include <errno.h>

int	mini_cd(t_cmd *cmd)
{
	char	*home;
	int		ret;

	// add check to see if path exists!
	if (cmd->params[1])
		ret = chdir(cmd->params[1]);
	else
	{
		home = getenv("HOME");
		if (!home)
			exit_shell_w_error(cmd, ERR_ENV_NOT_SET);
		ret = chdir(home);
	}
	if (ret < 0)
		return (errno);
	return (0);
}
