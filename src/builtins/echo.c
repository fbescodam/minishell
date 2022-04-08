/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 17:21:57 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/08 23:02:08 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

int	mini_echo(int is_child, t_cmd *cmd)
{
	size_t	i;
	char	add_nl;
	char	*temp;

	if (!is_child)
		return (0);
	add_nl = 1;
	i = 1;
	while (cmd->params[i] && ft_strncmp("-n\0", cmd->params[i], 3) == 0)
	{
		add_nl = 0;
		i++;
	}
	while (cmd->params[i])
	{
		ft_putstr_fd(cmd->params[i], 1);
		if (cmd->params[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (add_nl)
		ft_putchar_fd('\n', 1);
	return (0);
}
