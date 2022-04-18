/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 23:21:22 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/18 20:45:12 by jgalloni      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "structs.h"

void	free_cmd(void *cmd);
void	free_envar(void *envar);
void	free_mini(t_mini *mini);
char	*skip_chars(char *prompt, char *mask_set);
int		remove_character(char **str, char rem);
char	*get_next_single_quote(char *str);
int		scan_operators(char *prompt, char *operators, int quote_is_operator);
int		double_quote_check(char *prompt, int first_quote_index);
size_t	char_array_len(char **arr);
int		add_string_to_array(char ***to, char *from);
char	replace_space_with_null(unsigned int pos, char c);
int		get_quoted_string(char *prompt, char **dest);
int		join_realloc(char **dest, char *src, char len);
void	print_builtin_err(char *method, char *helping_hand, char *err);
int		is_fd_redir(char *prompt);
t_cmd	*get_cmd_from_pid(t_list *cmds, int pid);
void	fork_read_child(char *delimiter, int read_nl, int fd[2]);
void	write_heredoc(t_cmd *cmd, t_mini *mini);
int		is_valid_env_name_char(size_t pos, char c);
int		join_parsed_str(char **parsed_str, char *str);
char	*strdup_for_envar_val(char *str);
int		replace_tabs(char **prompt);

#endif
