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

int		mini_exit(int is_child, t_cmd *cmd);
int		mini_cd(int is_child, t_cmd *cmd);
int		mini_pwd(int is_child, t_cmd *cmd);
int		mini_echo(int is_child, t_cmd *cmd);
int		mini_export(int is_child, t_cmd *cmd);
int		mini_env(int is_child, t_cmd *cmd);
int		mini_unset(int is_child, t_cmd *cmd);
int		is_reserved(t_cmd *cmd);
int		run_reserved(int is_child, t_cmd *cmd);
int		run_in_child_only(int which);

#endif
