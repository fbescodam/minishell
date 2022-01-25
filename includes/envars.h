#ifndef ENVARS_H
# define ENVARS_H

# include "../libft/libft.h"
# include "structs.h"

t_ditem		*get_envar_item(t_dlist *envars, char *name);
t_envar		*get_envar(t_dlist *envars, char *name);
int			replace_envar_value(t_envar *envar, char *new_val);
int			set_envar(t_dlist *envars, char *name, char *val);

#endif
