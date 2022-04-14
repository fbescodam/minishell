/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   garbage.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 17:21:57 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/14 23:16:27 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "libft.h"

/**
 * @brief Free a token struct. The contents are not freed if flag is CMD, as
 * then the contents were freed in free_cmd (contents is then a reference to
 * the params pointer in the t_cmd struct).
 * @param[in] token the token to free
 */
void	free_token(void *token)
{
	if (!token)
		return ;
	if (((t_token *)token)->flag != PIPE_IN)
		ft_free(((t_token *)token)->content);
	ft_free(token);
}

void	free_cmd(void *cmd)
{
	if (!cmd)
		return ;
	ft_free(((t_cmd *)cmd)->heredoc);
	ft_free_double_ptr((void **)((t_cmd *)cmd)->params);
	ft_lstclear(&((t_cmd *)cmd)->tokens, &free_token);
	if (((t_cmd *)cmd)->path)
		ft_free(((t_cmd *)cmd)->path);
	if (((t_cmd *)cmd)->frake_err)
		ft_lstclear(&((t_cmd *)cmd)->frake_err, &free);
	ft_free(cmd);
}

void	free_envar(void *envar)
{
	if (!envar)
		return ;
	ft_free(((t_envar *)envar)->name);
	ft_free(((t_envar *)envar)->val);
	ft_free(((t_envar *)envar)->export);
	ft_free(envar);
}

void	free_mini(t_mini *mini)
{
	if (!mini)
		return ;
	if (mini->envars)
		ft_dlstclear(mini->envars, &free_envar);
	if (mini->cmds)
		ft_lstclear(&mini->cmds, &free_cmd);
	if (mini->paths)
		ft_free_double_ptr((void **)mini->paths);
	if (mini->prompt)
		ft_free(mini->prompt);
}
