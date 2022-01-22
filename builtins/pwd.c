/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/19 23:02:13 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/22 18:13:10 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include "../utils.h"

int	mini_pwd(t_cmd *cmd)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (ENOMEM);
	printf("%s\n", path);
	ft_free(path);
	return (0);
}
