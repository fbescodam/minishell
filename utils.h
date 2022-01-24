/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jgalloni <jgalloni@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/26 23:46:20 by jgalloni      #+#    #+#                 */
/*   Updated: 2022/01/24 18:01:37 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "libft/libft.h"
# include "tokens.h"

# define IN_FILE 8
# define IN_FD 4
# define OUT_FILE 2
# define OUT_FD 1

void	stop_server(int sig);
char	*check_command(t_cmd *cmd, char **paths);
int		is_reserved(t_cmd *cmd);
int		check_run_reserved_cmds(t_cmd *cmd);
char	**get_path(void);
int		input_redirect(int mode, t_cmd *cmd);
int		output_redirect(int mode, t_cmd *cmd);
int		cmd_redirection(t_cmd *cmd, t_list **current_token);
void	execute_command(t_cmd *cmd, char **paths);
void	sig_handler(int sig);
void	exit_shell_w_error(t_cmd *cmd, int err);
int		char_array_len(char **arr);
void	append_char_array(char **from, char **to);
int		add_arguments(t_cmd **cmd, t_token	*token);
int		get_envar_as_list(t_list **list, t_list *envars, char *name);
int		get_envar(t_envar **envar, t_list *envars, char *name);
t_envar	*set_envar(t_cmd *cmd, char *name, char *val);
int		parse_envars(t_list *envars, char **str);
void	free_cmd(void *cmd);
void	free_envar(void *envar);
void	free_mini(t_mini *mini);
int		scan_operators(char *prompt, char *operators);
int		add_string_to_array(char ***to, char *from);
t_list	*setup_cmds(t_mini *mini, t_list **cmds);
int		char_array_len(char **arr);
void	error_handler(t_cmd *cmd, int err);
void	print_token_list(t_list *tokens);

#endif
