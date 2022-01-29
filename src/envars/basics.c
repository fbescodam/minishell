#include "libft.h"
#include "structs.h"
#include "utils.h"
#include "envars.h"
	#include <stdio.h>

/**
 * @brief Get an environment variable from the list as item, by name
 *
 * @param envars The list of environment variables
 * @param name The name of the variable to look for
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
 * @param envars The list of environment variables
 * @param name The name of the variable to look for
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
 * @param envar The environment variable to modify
 * @param new_val The new value to set, allocated by malloc, cannot be NULL
 * @return Returns 1 on success and 0 on failure
 */
int	replace_envar_value(t_envar *envar, char *new_val)
{
	if (!new_val)
		return (0);
	ft_free(&envar->val);
	envar->val = new_val;
	if (!envar->val)
		return (0);
	return (1);
}

/**
 * @brief Add a variable to the list of environment variables
 *
 * @param envars The list of environment variables
 * @param name The name of the variable to set
 * @param val The value of the variable to set
 * @return Returns 0 on failure, 1 on success
 */
int	set_envar(t_mini *mini, char *name, char *val)
{
	t_envar		*envar;
	t_ditem		*list_item;

	envar = get_envar(mini->envars, name);
	if (envar)
		return (replace_envar_value(envar, ft_strdup(val)));
	envar = ft_calloc(1, sizeof(t_envar));
	if (!envar)
		return (0);
	envar->hash = ft_strhash(name, ft_strlen(name));
	envar->name = ft_strdup(name);
	envar->val = ft_strdup(val);
	list_item = ft_ditemnew(envar);
	if (!list_item || !envar->name || !envar->val)
	{
		ft_dlstdelone(list_item, &free_envar);
		return (0);
	}
	if (envar->hash == PATH_HASH && !set_mini_paths(mini, list_item))
		return (0);
	ft_dlstadd_back(mini->envars, list_item);
	return (1);
}
