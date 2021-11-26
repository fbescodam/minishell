/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putchar_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 13:28:30 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:24:36 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Write a character to a file descriptor
 * @param c		The character to write
 * @param fd	The file descriptor to write to
 * @return		The amount of characters written, or -1 on error
 */
int	ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}
