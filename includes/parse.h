#ifndef PARSE_H
# define PARSE_H

int		parse_prompt(t_mini *mini, char *prompt);
int		setup_cmds(t_mini *mini, char **prompts);
int		parse_input_redir(char *prompt, t_cmd *cmd);
#endif
