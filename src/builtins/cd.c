/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 17:21:57 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/14 21:25:56 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"
#include "envars.h"
#include "custom_errors.h"

static int	set_path_envar(t_cmd *cmd)
{
	t_envar	*envar;
	char	*path;
	int		ret;

	path = getcwd(NULL, 0);
	if (!path)
		return (ENOMEM);
	envar = get_envar(cmd->mini->envars, "PWD");
	if (envar)
		ret = replace_envar_value(cmd->mini, envar, path);
	else
		ret = set_envar(cmd->mini, "PWD", path, 0);
	free(path);
	if (!ret)
		return (ENOMEM);
	return (0);
}

int	mini_cd(int is_child, t_cmd *cmd)
{
	t_envar	*envar;
	char	*path;

	if (cmd->params[1])
		path = cmd->params[1];
	else
	{
		envar = get_envar(cmd->mini->envars, "HOME");
		if (!envar)
			return (ENOENT);
		path = envar->val;
	}
	if (chdir(path) < 0)
		return (errno);
	if (!is_child)
		return (set_path_envar(cmd));
	return (0);
}
