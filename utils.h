/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jgalloni <jgalloni@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/26 23:46:20 by jgalloni      #+#    #+#                 */
/*   Updated: 2021/11/26 23:47:08 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef struct t_cmd_utils{
	char	*in_file;
	char	*out_file;
	int		in_fd;
	int		out_fd;
	char	**params;
	char	*path;
}t_cmd;

# define IN_FILE 8
# define IN_FD 4
# define OUT_FILE 2
# define OUT_FD 1

void	stop_server(int sig);
char	*check_command(char *command, char **paths);
char	**set_path(void);
int		input_redirect(int mode, t_cmd *cmd);
int		output_redirect(int mode, t_cmd *cmd);
void	execute_command(int mode, t_cmd *cmd, char **paths);
void	exit_shell(int sig);
void	exit_shell_w_error(int err);
#endif
