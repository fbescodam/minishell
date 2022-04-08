/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 22:08:44 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/08 23:06:26 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLING_H
# define ERROR_HANDLING_H

# include "structs.h"
# include "custom_errors.h"

void	force_exit(t_mini *mini, int err);
void	error_manager(t_mini *mini, int err);

#endif
