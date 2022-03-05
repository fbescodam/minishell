#ifndef SETUP_H
# define SETUP_H

# include "structs.h"

# define KUT "\1\e[1;40;31m\2hell\1\e[0;7;40;31m\2shell\1\e[0;1m\2> \1\e[0m\2"

int			setup_mini(t_mini *mini, char *shellname, char **envp);
int			setup_signals(t_mini *mini);

#endif
