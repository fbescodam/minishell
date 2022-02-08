#ifndef PARSE_H
# define PARSE_H

int		parse_prompt(t_mini *mini, char *prompt);
int		setup_cmds(t_mini *mini, char **prompts);
int		parse_input_redir(char *prompt, t_cmd *cmd);
int		parse_params(char *prompt, char ***dest);
int		search_params(char **buff, char **prompt, char ***dest);
int		add_param(char **param_buffer, char ***dest);
#endif
