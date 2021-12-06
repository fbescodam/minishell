/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jgalloni <jgalloni@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/26 23:46:20 by jgalloni      #+#    #+#                 */
/*   Updated: 2021/12/06 15:33:46 by jgalloni      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
#include "libft/libft.h"

typedef struct t_cmd_utils{
	char	*in_file;
	char	*out_file;
	int		in_fd;
	int		out_fd;
	int		mode;
	char	**params;
	char	*path;
	t_list	*tokens;
}t_cmd;

# define IN_FILE 8
# define IN_FD 4
# define OUT_FILE 2
# define OUT_FD 1



void	stop_server(int sig);
char	*check_command(t_cmd *cmd, char **paths);
int		check_run_reserved_cmds(t_cmd *cmd);
char	**set_path(void);
int		input_redirect(int mode, t_cmd *cmd);
int		output_redirect(int mode, t_cmd *cmd);
void	execute_command(t_cmd *cmd, char **paths);
void	sig_handler(int sig);
void	exit_shell_w_error(int err);
#endif
