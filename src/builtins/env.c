/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 17:21:57 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/08 23:01:49 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "utils.h"

int	mini_env(int is_child, t_cmd *cmd)
{
	size_t	i;
	t_ditem	*item;

	if (!is_child)
		return (0);
	i = 0;
	item = cmd->mini->envars->first;
	while (i < cmd->mini->envars->size)
	{
		if (((t_envar *)item->content)->export)
			printf("%s\n", ((t_envar *)item->content)->export);
		item = item->next;
		i++;
	}
	return (0);
}
