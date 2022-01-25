#include "../libft/libft.h"
#include "structs.h"
#include "utils.h"

/**
 * @brief Get an environment variable from the list, by name
 *
 * @param envars The list of environment variables
 * @param name The name of the variable to look for
 * @return t_ditem*
 */
t_ditem	*get_envar(t_dlist *envars, char *name)
{
	t_ditem		*temp;
	size_t		name_len;
	size_t		i;

	name_len = ft_strlen(name);
	i = 0;
	temp = envars->first;
	while (i < envars->size)
	{
		if (ft_strncmp(((t_envar *)temp->content)->name, name, name_len) == 0)
			return (temp);
		temp = temp->next;
		i++;
	}
	return (NULL);
}

/**
 * @brief Set the envar object
 *
 * @param envars
 * @param name
 * @param val
 * @return int
 */
int	set_envar(t_dlist *envars, char *name, char *val)
{
	t_envar		*envar;
	t_ditem		*list_item;

	get_envar(envars, name);
	if (envar)
	{
		ft_free(envar->val);
		envar->val = ft_strdup(val);
		if (!envar->val)
			return (0);
		return (1);
	}
	envar = ft_calloc(1, sizeof(t_envar));
	if (!envar)
		return (0);
	envar->name = ft_strdup(name);
	envar->val = ft_strdup(val);
	list_item = ft_ditemnew(envar);
	if (!list_item || !envar->name || !envar->val)
	{
		ft_dlstdelone(list_item, &free_envar);
		return (0);
	}
	ft_dlstadd_back(envars, list_item);
	return (1);
}
