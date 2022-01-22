/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envars.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 17:58:55 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/22 18:54:32 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "errno.h"

/**
 * @brief Get an environment variable from the list
 *
 * @param list This pointer will point to the list item if it is found
 * @param cmd The cmd structure to search through
 * @param name The name of the environment variable to find
 * @return int The index of the environment variable in the list
 */
int	get_envar_as_list(t_list **list, t_cmd *cmd, char *name)
{
	int		i;
	t_list	*temp;
	size_t	name_len;

	name_len = ft_strlen(name);
	temp = cmd->mini->envars;
	i = 0;
	while (temp)
	{
		if (ft_strncmp(((t_envar *)temp->content)->name, name, name_len) == 0)
		{
			*list = temp;
			return (i);
		}
		temp = temp->next;
		i++;
	}
	*list = NULL;
	return (-1);
}

/**
 * @brief Get an environment variable from the list
 *
 * @param envar This pointer will point to the envar if it is found
 * @param cmd The cmd structure to search through
 * @param name The name of the environment variable to find
 * @return int The index of the environment variable in the list
 */
int	get_envar(t_envar **envar, t_cmd *cmd, char *name)
{
	t_list	*temp;
	int		index;

	index = get_envar_as_list(&temp, cmd, name);
	if (index > -1)
		*envar = (t_envar *)temp->content;
	else
		*envar = NULL;
	return (index);
}

t_envar	*set_envar(t_cmd *cmd, char *name, char *val)
{
	t_envar		*envar;
	t_list		*list_elem;

	get_envar(&envar, cmd, name);
	if (envar)
	{
		ft_free(envar->val);
		envar->val = ft_strdup(val);
		if (!envar->val)
			exit_shell_w_error(cmd, ENOMEM);
		return (0);
	}
	envar = ft_calloc(1, sizeof(t_envar));
	if (!envar)
		exit_shell_w_error(cmd, ENOMEM);
	envar->name = ft_strdup(name);
	envar->val = ft_strdup(val);
	list_elem = ft_lstnew(envar);
	if (!list_elem || !envar->name || !envar->val)
	{
		free_envar(envar);
		ft_free(list_elem);
		exit_shell_w_error(cmd, ENOMEM);
	}
	ft_lstadd_back(&(cmd->mini->envars), (void *)list_elem);
	return (envar);
}
