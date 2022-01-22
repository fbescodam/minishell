#ifndef PARSE_H
# define PARSE_H

int		split_prompt(char *prompt, char ***prompts, char c);
int		parse_prompt(char *prompt, t_list *cmds, t_mini *mini);
int		parse_command(t_list *cmds, char *prompt);

#endif
