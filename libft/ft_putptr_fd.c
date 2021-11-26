/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putptr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/02 18:37:56 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:25:13 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ptr_loop(intptr_t ptr, int fd)
{
	static char	base[] = "0123456789abcdef";
	int			written_chars;

	written_chars = 0;
	if (ptr != 0)
	{
		written_chars = ptr_loop(ptr / 16, fd);
		return (written_chars + write(fd, &base[ptr % 16], 1));
	}
	return (written_chars);
}

/**
 * Write a pointer address to a file descriptor
 * @param ptr	The pointer to write
 * @param fd	The file descriptor to write to
 * @return		The amount of characters written, or -1 on error
 */
int	ft_putptr_fd(intptr_t ptr, int fd)
{
	int			written_chars;

	written_chars = write(fd, "0x", 2);
	if (ptr == 0)
		return (written_chars + write(fd, "0", 1));
	return (written_chars + ptr_loop(ptr, fd));
}
