/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 17:21:57 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/08 23:00:51 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "utils.h"

int	mini_pwd(int is_child, t_cmd *cmd)
{
	char	*path;

	if (!is_child)
		return (0);
	path = getcwd(NULL, 0);
	if (!path)
		return (ENOMEM);
	printf("%s\n", path);
	ft_free(path);
	return (0);
}
