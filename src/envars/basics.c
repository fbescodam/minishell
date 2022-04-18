/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   basics.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 17:21:57 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/18 19:20:12 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include "utils.h"
#include "envars.h"
#include <stdlib.h>

static int	replace_envar_export(t_envar *envar, char *new_val)
{
	char	*temp;
	size_t	len;
	char	*eq;
	size_t	len_until_eq;

	len = ft_strlen(new_val);
	eq = ft_strchr(envar->export, '=');
	*eq = '\0';
	temp = ft_calloc(eq - envar->export + len + 2, sizeof(char));
	if (!temp)
		return (0);
	len_until_eq = eq - envar->export;
	ft_memcpy(temp, envar->export, len_until_eq);
	temp[len_until_eq] = '=';
	ft_memcpy(&temp[len_until_eq + 1], new_val, len);
	free(envar->export);
	envar->export = temp;
	return (1);
}

/**
 * @brief Get an environment variable from the list as item, by name
 *
 * @param[in] envars The list of environment variables
 * @param[in] name The name of the variable to look for
 * @return The environment variable, contained in a double linked list item
 */
t_ditem	*get_envar_item(t_dlist *envars, char *name)
{
	unsigned int	hash_to_find;
	t_ditem			*temp;
	size_t			i;

	hash_to_find = ft_strhash(name, ft_strlen(name));
	i = 0;
	temp = envars->first;
	while (i < envars->size)
	{
		if (hash_to_find == ((t_envar *)temp->content)->hash)
			return (temp);
		temp = temp->next;
		i++;
	}
	return (NULL);
}

/**
 * @brief Get an environment variable from the list, by name
 *
 * @param[in] envars The list of environment variables
 * @param[in] name The name of the variable to look for
 * @return The environment variable structure
 */
t_envar	*get_envar(t_dlist *envars, char *name)
{
	t_ditem		*temp;

	temp = get_envar_item(envars, name);
	if (temp)
		return ((t_envar *)temp->content);
	return (NULL);
}

/**
 * @brief Replace the value of an existing environment variable
 *
 * @param[in] mini Mini struct
 * @param[in] envar The environment variable to modify
 * @param[in] new_val The new value to set, will be strduped
 * @return Returns 0 on failure, 1 on success
 */
int	replace_envar_value(t_mini *mini, t_envar *envar, char *new_val)
{
	if (!new_val)
		return (0);
	ft_free(envar->val);
	envar->val = strdup_for_envar_val(new_val);
	if (!envar->val)
		return (0);
	if (envar->export && !replace_envar_export(envar, new_val))
		return (0);
	if (!envar->val
		|| (envar->hash == PATH_HASH && !set_mini_paths(mini, envar->val)))
		return (0);
	return (1);
}

/**
 * @brief Add a variable to the list of environment variables
 *
 * @param[in] mini The main mini struct
 * @param[in] name The name of the variable to set
 * @param[in] val The value of the variable to set
 * @param[in] export Whether or not the variable should be exported to execve
 * @return Returns 0 on failure, 1 on success
 */
int	set_envar(t_mini *mini, char *name, char *val, int export)
{
	t_envar		*envar;
	t_ditem		*list_item;

	envar = get_envar(mini->envars, name);
	if (envar)
		return (replace_envar_value(mini, envar, val));
	envar = ft_calloc(1, sizeof(t_envar));
	if (!envar)
		return (0);
	envar->hash = ft_strhash(name, ft_strlen(name));
	envar->name = ft_strdup(name);
	envar->val = strdup_for_envar_val(val);
	if (export)
		envar->export = ft_str3join(name, "=", val);
	list_item = ft_ditemnew(envar);
	if (!list_item || !envar->name || !envar->val || (export && !envar->export)
		|| (envar->hash == PATH_HASH && !set_mini_paths(mini, envar->val)))
	{
		ft_dlstdelone(list_item, &free_envar);
		return (0);
	}
	ft_dlstadd_back(mini->envars, list_item);
	return (1);
}
