#ifndef EXECUTE_H
# define EXECUTE_H

int		input_redirect(t_token *token);
int		output_redirect(t_token *token);
int		check_command(t_cmd *cmd, t_mini *mini);
int		execute_list(t_mini *mini);
int		is_reserved(t_cmd *cmd);
int		check_run_reserved_cmds(t_cmd *cmd, int which);
int		run_in_child(int which);
void	child_process(t_cmd *cmd);
int		heredoc_redirect(t_cmd *cmd);
void	wait_n_processes(int amount, t_mini *mini);

#endif
