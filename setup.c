/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jgalloni <jgalloni@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/26 23:46:37 by jgalloni      #+#    #+#                 */
/*   Updated: 2022/01/22 21:10:07 by jgalloni      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "custom_errors.h"
#include "tokens.h"
#include <stdio.h>
#include <errno.h>

char	*find_cmd(t_cmd *cmd)
{
	t_token	*token;
	t_list	*current;
	char	**params;

	current = cmd->tokens;
	while (current)
	{
		token = (t_token *)(current->content);
		if (token->flag == CMD)
		{
			params = (char **)(token->content);
			cmd->params = params;
			return (ft_strdup(params[0]));
		}
		current = current->next;
	}
	cmd->params = 0;
	return (NULL);
}

char	*check_command(t_cmd *cmd, char **paths)
{
	char	*command;
	char	*new_path;
	char	*temp;
	int		i;

	i = 0;
	command = find_cmd(cmd);
	if (!command)
		return (NULL);
	if (command[0] == '.' && command[1] == '/' && access(command, R_OK) == 0)
		return (command);
	temp = ft_strjoin("/", command);
	ft_free(command);
	while (paths[i])
	{
		new_path = ft_strjoin(paths[i], temp);
		if (new_path && access(new_path, R_OK) == 0)
		{
			free(temp);
			return (new_path);
		}
		free(new_path);
		i++;
	}
	free(temp);
	return (NULL);
}

int	setup_cmds(t_mini *mini, t_list **cmds)
{
	t_cmd	*cmd;
	t_list	*cmd_instance;

	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (ENOMEM);
	cmd->mini = mini;
	if (!(*cmds))
		*cmds = ft_lstnew(cmd);
	if (!cmds)
	{
		free(cmd);
		return (ENOMEM);
	}
	return (0);
}

char	**get_path(void)
{
	char	*env;
	char	**paths;

	env = getenv("PATH");
	if (!env)
		exit_shell_w_error(NULL, ERR_PATH_MISSING);
	paths = ft_split(env, ':');
	if (!paths)
		exit_shell_w_error(NULL, ENOMEM);
	return (paths);
}
