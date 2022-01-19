/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jgalloni <jgalloni@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/26 23:46:37 by jgalloni      #+#    #+#                 */
/*   Updated: 2022/01/20 00:26:53 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "tokens.h"
#include <stdio.h>

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

char	**set_path()
{
	char	*env;
	char	**paths;

	env = getenv("PATH");
	paths = ft_split(env, ':');
	//protect this laterrrr
	return (paths);
}
