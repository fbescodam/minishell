/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envars.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 17:58:55 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/20 19:01:00 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "errno.h"

static t_envar	*get_existing_envar(t_cmd *cmd, char *name)
{
	t_list	*temp;
	size_t	name_len;

	name_len = ft_strlen(name);
	temp = cmd->mini->envars;
	while (temp)
	{
		if (ft_strncmp(((t_envar *)temp->content)->name, name, name_len) == 0)
			return ((t_envar *)temp->content);
		temp = temp->next;
	}
	return (NULL);
}

t_envar	*set_envar(t_cmd *cmd, char *name, char *val)
{
	t_envar		*envar;
	t_list		*list_elem;

	envar = get_existing_envar(cmd, name);
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
		exit_shell_w_error(cmd, ENOMEM);
	ft_lstadd_back(&(cmd->mini->envars), (void *)list_elem);
	return (envar);
}
