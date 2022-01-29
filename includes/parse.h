#ifndef PARSE_H
# define PARSE_H

int		scan_operators(char *prompt, char *operators, int quote_is_operator);
char	*skip_chars(char *prompt, char *mask_set);
int		parse_prompt(t_mini *mini, char *prompt);
int		add_string_to_array(char ***to, char *from);

#endif
