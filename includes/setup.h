#ifndef SETUP_H
# define SETUP_H

# include "structs.h"

# define KUT "\001\x1b[1;40;31m\002hell\001\x1b[0m\x1b[7;40;31m\002shell\001\x1b[0m\x1b[1m\002> \001\x1b[0m\002"

int			setup_mini(t_mini *mini, char **envp);
int			setup_signals(t_mini *mini);

#endif
