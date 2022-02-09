#ifndef EXECUTE_H
# define EXECUTE_H

int		check_command(t_cmd *cmd, t_mini *mini);
int		execute_list(t_mini *mini);
int		is_reserved(t_cmd *cmd);
int		check_run_reserved_cmds(t_cmd *cmd, int which);
int		run_in_child(int which);

#endif
