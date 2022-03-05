#ifndef BUILTINS_H
# define BUILTINS_H

# include "structs.h"

# define MINI_BUILTIN_NONE 0
# define MINI_BUILTIN_CD 1
# define MINI_BUILTIN_ECHO 2
# define MINI_BUILTIN_ENV 3
# define MINI_BUILTIN_EXIT 4
# define MINI_BUILTIN_EXPORT 5
# define MINI_BUILTIN_PWD 6
# define MINI_BUILTIN_UNSET 7

int		mini_exit(t_cmd *cmd);
int		mini_cd(t_cmd *cmd);
int		mini_pwd(t_cmd *cmd);
int		mini_echo(t_cmd *cmd);
int		mini_export(t_cmd *cmd);
int		mini_env(t_cmd *cmd);
int		mini_unset(t_cmd *cmd);
int		is_reserved(t_cmd *cmd);
int		run_reserved(t_cmd *cmd);
int		run_in_child(int which);

#endif
