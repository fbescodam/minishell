#ifndef SETUP_H
# define SETUP_H

# include "structs.h"

# define KUT "\001\e[1;40;31m\002hell\001\e[0m\e[7;40;31m\002shell\001\e[0m\e[1m\002> \001\e[0m\002"

int			setup_mini(t_mini *mini, char *shellname, char **envp);
int			setup_signals(t_mini *mini);

#endif
