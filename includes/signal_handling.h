/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handling.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 22:08:44 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/18 16:47:34 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLING_H
# define SIGNAL_HANDLING_H

void	sig_handler(int sig);
void	exec_sig_handler(int sig);
void	hdoc_sig_parent(int sig);

#endif
