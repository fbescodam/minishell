/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   garbage.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 00:30:19 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/20 19:03:08 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "tokens.h"
	#include <stdio.h>

/**
 * @brief Free a token struct. The contents are not freed if flag is CMD, as
 * then the contents were freed in free_cmd (contents is then a reference to
 * the params pointer in the t_cmd struct).
 *
 * @param token the token to free
 */
void	free_token(void *token)
{
	if (!token)
		return ;
	if (((t_token *)token)->flag != CMD)
		ft_free(((t_token *)token)->content);
	ft_free(token);
}

void	free_cmd(void *cmd)
{
	if (!cmd)
		return ;
	ft_free_double_ptr((void **)((t_cmd *)cmd)->params);
	ft_lstclear(&((t_cmd *)cmd)->tokens, &free_token);
	ft_free(((t_cmd *)cmd)->path);
	ft_free(cmd);
}

void	free_envar(void *envar)
{
	if (!envar)
		return ;
	ft_free(((t_envar *)envar)->name);
	ft_free(((t_envar *)envar)->val);
	ft_free(envar);
}

void	free_mini(t_mini *mini)
{
	if (!mini)
		return ;
	ft_lstclear(&mini->envars, &free_envar);
}
