/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 22:08:44 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/08 23:40:59 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "structs.h"

void	print_char_array(char **arr);
void	print_tokens(t_list *tokens);
void	print_command_list(t_list *cmds);
void	print_command_status(t_cmd *cmd, int ret);
void	print_path_pid(t_list *cmds, int pid);

#endif
