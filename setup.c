/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jgalloni <jgalloni@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/26 23:46:37 by jgalloni      #+#    #+#                 */
/*   Updated: 2021/12/05 19:44:18 by jgalloni      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "tokens.h"
#include <stdio.h>

char	*find_cmd(t_list *tokens)
{
	t_token	*token;
	t_list *current;
	char **params;
	
	current = tokens;
	while (current)
	{
		token = (t_token *)(current->content);
		if (token->flag == WORD)
		{
			params = (char **)(token->content);
			return (params[0]);
		}
		current = current->next;
	}
	return (0);
}

char	*check_command(t_list *tokens, char **paths)
{
	char *command;
	char	*new_path;
	char	*temp;
	int		i;

	i = 0;
	command = find_cmd(tokens);
	if (access(command, R_OK) == 0)
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
	return (0);
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
