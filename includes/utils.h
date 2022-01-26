#ifndef UTILS_H
# define UTILS_H

void	free_token(void *token);
void	free_cmd(void *cmd);
void	free_envar(void *envar);
void	free_mini(t_mini *mini);
int 	skip_over_single_quotes(char **str);
int		remove_character(char **str, char rem);

#endif
