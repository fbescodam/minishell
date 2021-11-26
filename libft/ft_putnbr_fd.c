/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/12 18:42:02 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:25:01 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Write a number to a file descriptor
 * @param n		The number to write
 * @param fd	The file descriptor to write to
 * @return		The amount of characters written, or -1 on error
 */
int	ft_putnbr_fd(int n, int fd)
{
	int		writes;

	writes = 0;
	if (n == -2147483648)
		return (write(fd, "-2147483648", 11));
	if (n < 0)
	{
		writes += write(fd, "-", 1);
		n *= -1;
	}
	return (writes + ft_putnbr_base_fd((unsigned int)n, "0123456789", fd));
}
