/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 17:21:57 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/14 23:18:36 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "utils.h"
#include "builtins.h"
#include "envars.h"

static void	export_err(char *id)
{
	print_builtin_err("export", id, "not a valid identifier");
}

static int	export_only(int is_child, size_t i, t_cmd *cmd)
{
	t_envar	*envar;

	if (!is_valid_env_name(cmd->params[i]) && is_child)
		export_err(cmd->params[i]);
	envar = get_envar(cmd->mini->envars, cmd->params[i]);
	if (envar)
	{
		ft_free(envar->export);
		envar->export = ft_str3join(envar->name, "=", envar->val);
	}
	if (envar && !envar->export)
		return (0);
	return (1);
}

static int	set_and_export(int is_child, int i, t_cmd *cmd, char *equals_pos)
{
	if (!is_valid_env_name(cmd->params[i]) && is_child)
		export_err(cmd->params[i]);
	else
	{
		*equals_pos = '\0';
		if (!set_envar(cmd->mini, cmd->params[i], equals_pos + 1, 1))
			return (0);
	}
	return (1);
}

int	mini_export(int is_child, t_cmd *cmd)
{
	size_t	i;
	char	*equals_pos;

	if (char_array_len(cmd->params) < 2)
		return (mini_env(is_child, cmd));
	i = 1;
	while (cmd->params[i])
	{
		equals_pos = ft_strchr(cmd->params[i], '=');
		if (equals_pos == cmd->params[i] && is_child)
			export_err(cmd->params[i]);
		else if (equals_pos && !set_and_export(is_child, i, cmd, equals_pos))
			return (ENOMEM);
		else if (!export_only(is_child, i, cmd))
			return (ENOMEM);
		i++;
	}
	return (0);
}
