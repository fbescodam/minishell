/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   garbage.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 00:30:19 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/20 00:34:44 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "tokens.h"

void	free_token(void *token)
{
	if (token)
		ft_free(((t_token *)token)->content);
	ft_free(token);
}

void	free_cmd(void *cmd)
{
	if (cmd)
	{
		ft_free_double_ptr((void **)((t_cmd *)cmd)->params);
		ft_lstclear(&((t_cmd *)cmd)->tokens, &free_token);
		ft_free(((t_cmd *)cmd)->path);
	}
	ft_free(cmd);
}
