#ifndef DEBUG_H
# define DEBUG_H
# include "structs.h"

void	print_char_array(char **arr);
void	print_tokens(t_list *tokens);
void	print_command_list(t_list *cmds);
void	print_command_status(t_cmd *cmd, int ret);
void	print_path_pid(t_list *cmds, int pid);

#endif
