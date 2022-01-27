#ifndef BUILTINS_H
# define BUILTINS_H

# include "structs.h"

int		mini_exit(t_cmd *cmd);
int		mini_cd(t_cmd *cmd);
int		mini_pwd(t_cmd *cmd);
int		mini_echo(t_cmd *cmd);
int		mini_export(t_cmd *cmd);
int		mini_env(t_cmd *cmd);
int		mini_unset(t_cmd *cmd);

#endif
