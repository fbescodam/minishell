/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 21:51:22 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/25 22:48:15 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

/**
 * Write a string to a file descriptor and end with a newline
 * @param *s	The string to write
 * @param fd	The file descriptor to write to
 * @return		The amount of characters written, or -1 on error
 */
int	ft_putendl_fd(char *s, int fd)
{
	int	written_chars;

	written_chars = ft_putstr_fd(s, fd);
	written_chars += ft_putchar_fd('\n', fd);
	return (written_chars);
}
