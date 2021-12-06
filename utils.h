/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jgalloni <jgalloni@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/26 23:46:20 by jgalloni      #+#    #+#                 */
/*   Updated: 2021/12/06 20:05:53 by jgalloni      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
#include "libft/libft.h"
#include "tokens.h"

typedef struct t_cmd_utils{
	char	*in_file;
	char	*out_file;
	int		in_fd;
	int		out_fd;
	int		mode;
	char	**params;
	char	*path;
	t_list	*tokens;
	int		argc;
}t_cmd;

# define IN_FILE 8
# define IN_FD 4
# define OUT_FILE 2
# define OUT_FD 1



void	stop_server(int sig);
char	*check_command(t_cmd *cmd, char **paths);
int		is_reserved(t_cmd *cmd);
int		check_run_reserved_cmds(t_cmd *cmd);
char	**set_path(void);
int		input_redirect(int mode, t_cmd *cmd);
int		output_redirect(int mode, t_cmd *cmd);
int		cmd_redirection(t_cmd *cmd, t_list **current_token);
void	execute_command(t_cmd *cmd, char **paths);
void	sig_handler(int sig);
void	exit_shell_w_error(int err);
int		char_array_len(char **arr);
void	append_char_array(char **from, char **to);
int		add_arguments(t_cmd **cmd, t_token	*token);
#endif
