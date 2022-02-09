#ifndef EXECUTE_H
# define EXECUTE_H

int		input_redirect(t_token *token);
int		output_redirect(t_token *token);
int		check_command(t_cmd *cmd, t_mini *mini);
int		execute_list(t_mini *mini);
void	child_process(t_cmd *cmd);


#endif
