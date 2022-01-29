#ifndef ENVARS_H
# define ENVARS_H

# include "../libft/libft.h"
# include "structs.h"

# define PATH_HASH 0x68081897

t_ditem		*get_envar_item(t_dlist *envars, char *name);
t_envar		*get_envar(t_dlist *envars, char *name);
int			find_var_name_start(char *str, char **var_start);
char		*find_var_name_end(char *str);
int			replace_envar_value(t_envar *envar, char *new_val);
int			set_envar(t_mini *mini, char *name, char *val);
int			parse_envars(t_dlist *envars, char **str);
int			set_mini_paths(t_mini *mini, t_ditem *list_item);

#endif
