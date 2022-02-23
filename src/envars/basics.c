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
 * @param[in] new_val The new value to set, allocated by malloc, cannot be NULL
 * @return Returns 1 on success and 0 on failure
 */
int	replace_envar_value(t_envar *envar, char *new_val)
{
	if (!new_val)
		return (0);
	ft_free(envar->val);
	envar->val = new_val;
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
		return (replace_envar_value(envar, ft_strdup(val)));
	envar = ft_calloc(1, sizeof(t_envar));
	if (!envar)
		return (0);
	envar->hash = ft_strhash(name, ft_strlen(name));
	envar->name = ft_strdup(name);
	envar->val = ft_strdup(val);
	envar->export = export;
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

// TODO: error check on ft_va_add
char	**get_envars_as_envp(t_mini *mini)
{
	t_ft_va_item	**list;
	size_t			i;
	t_ditem			*item;
	char			*temp;
	char			**ret;

	i = 0;
	item = mini->envars->first;
	ret = (char **)ft_calloc(mini->envars->size + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	while (i < mini->envars->size)
	{
		list = ft_va_new(3);
		if (!list)
			return ((char **)ft_free_double_ptr((void **)ret));
		ft_va_add(list, 0, ((t_envar *)item->content)->name,
			ft_strlen(((t_envar *)item->content)->name) + 1);
		ft_va_add(list, 1, "=", 2);
		ft_va_add(list, 3, ((t_envar *)item->content)->val,
			ft_strlen(((t_envar *)item->content)->val) + 1);
		temp = ft_strxjoin(3, list);
		if (!temp)
			return ((char **)ft_free_double_ptr((void **)ret));
		ret[i] = temp;
		item = item->next;
		i++;
	}
	return (ret);
}
