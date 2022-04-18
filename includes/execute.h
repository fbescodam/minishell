/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jgalloni <jgalloni@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 20:06:29 by jgalloni      #+#    #+#                 */
/*   Updated: 2022/04/18 16:46:33 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

int		input_redirect(t_token *token);
int		output_redirect(t_token *token);
int		check_command(t_cmd *cmd, t_mini *mini);
int		execute_list(t_mini *mini);
void	child_process(t_cmd *cmd);
void	wait_n_processes(int amount, t_mini *mini);

#endif
