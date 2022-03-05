#ifndef UTILS_H
# define UTILS_H

# include "structs.h"

void	free_token(void *token);
void	free_cmd(void *cmd);
void	free_envar(void *envar);
void	free_mini(t_mini *mini);
int 	skip_over_single_quotes(char **str);
char	*skip_chars(char *prompt, char *mask_set);
int		remove_character(char **str, char rem);
char	*get_next_single_quote(char *str);
int		scan_operators(char *prompt, char *operators, int quote_is_operator);
int		double_quote_check(char *prompt, int first_quote_index);
int		split_and_add(char *from, char ***to, int split_index);
int		char_array_len(char **arr);
int		add_string_to_array(char ***to, char *from);
char	replace_space_with_null(unsigned int pos, char c);
int		get_quoted_string(char *prompt, char **dest);
int		join_realloc(char **dest, char *src, char len);
int		ptc_error(t_cmd *cmd, char *str);
void	print_ptc_errors(t_list *frake_err);
int		is_fd_redir(char *prompt);

#endif
