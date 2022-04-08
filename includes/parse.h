/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jgalloni <jgalloni@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 16:52:29 by jgalloni      #+#    #+#                 */
/*   Updated: 2022/04/08 23:04:50 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
#include "structs.h"


int		parse_prompt(t_mini *mini, char *prompt);
int		setup_cmds(t_mini *mini, char **prompts);
int		parse_input_redir(char *prompt, t_cmd *cmd);
int		parse_params(char *prompt, char ***dest);
int		search_params(char **buff, char **prompt, char ***dest);
int		add_param(char **param_buffer, char ***dest);
int		read_til_close_pipe(char ***to, t_mini *mini);
int		split_prompt(char *from, char ***to, char *set, t_mini *mini);
int		heredoc(t_cmd *cmd, char *delimiter);
#endif
