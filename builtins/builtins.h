/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/19 22:19:43 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/24 17:11:48 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../structs.h"

int		mini_exit(t_cmd *cmd);
int		mini_cd(t_cmd *cmd);
int		mini_pwd(t_cmd *cmd);
int		mini_echo(t_cmd *cmd);
int		mini_export(t_cmd *cmd);
int		mini_env(t_cmd *cmd);
int		mini_unset(t_cmd *cmd);

#endif
