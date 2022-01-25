/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 18:11:32 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/25 22:11:22 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "utils.h"

int	mini_env(t_cmd *cmd)
{
	t_list	*temp;

	temp = cmd->mini->envars;
	while (temp)
	{
		printf("%s=%s\n", ((t_envar *)temp->content)->name,
			((t_envar *)temp->content)->val);
		temp = temp->next;
	}
	return (0);
}
