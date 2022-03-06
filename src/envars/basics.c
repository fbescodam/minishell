#include "libft.h"
#include "structs.h"
#include "utils.h"
#include "envars.h"
	#include <stdio.h>

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
 * @param[in] envar The environment variable to modify
 * @param[in] new_val The new value to set, will be strduped
 * @return Returns 0 on failure, 1 on success
 */
int	replace_envar_value(t_envar *envar, char *new_val)
{
	if (!new_val)
		return (0);
	ft_free(envar->val);
	envar->val = ft_strdup(new_val);
	// TODO: replace envar->export if not NULL
	if (!envar->val)
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
		return (replace_envar_value(envar, val));
	envar = ft_calloc(1, sizeof(t_envar));
	if (!envar)
		return (0);
	envar->hash = ft_strhash(name, ft_strlen(name));
	envar->name = ft_strdup(name);
	envar->val = ft_strdup(val);
	if (export)
		envar->export = ft_str3join(name, "=", val);
	list_item = ft_ditemnew(envar);
	if (!list_item || !envar->name || !envar->val || (export && !envar->export))
	{
		ft_dlstdelone(list_item, &free_envar);
		return (0);
	}
	if (envar->hash == PATH_HASH && !set_mini_paths(mini, list_item))
		return (0);
	ft_dlstadd_back(mini->envars, list_item);
	return (1);
}

static size_t	get_amount_of_exported_envars(t_dlist *envars)
{
	size_t	i;
	size_t	amount;
	t_ditem	*item;

	item = envars->first;
	i = 0;
	amount = 0;
	while (i < envars->size)
	{
		if (((t_envar *)item->content)->export)
			amount++;
		item = item->next;
		i++;
	}
	return (amount);
}

char	**get_envars_as_envp(t_mini *mini)
{
	size_t			i;
	size_t			amount;
	t_ditem			*item;
	char			**ret;

	i = 0;
	amount = get_amount_of_exported_envars(mini->envars);
	item = mini->envars->first;
	ret = (char **)ft_calloc(amount + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	while (item)
	{
		if (((t_envar *)item->content)->export)
		{
			ret[i] = ((t_envar *)item->content)->export;
			i++;
		}
		item = item->next;
	}
	return (ret);
}
