/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_base_fd.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/02 17:49:16 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:24:53 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_valid_base(char *base)
{
	int		i;
	int		j;

	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		j = i + 1;
		while (base[j] != '\0')
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	if (i < 2)
		return (0);
	return (1);
}

static int	nbr_loop(unsigned int n, char *base, int base_num, int fd)
{
	int		written_chars;

	written_chars = 0;
	if (n != 0)
	{
		written_chars = nbr_loop(n / base_num, base, base_num, fd);
		return (write(fd, &base[n % base_num], 1));
	}
	return (written_chars);
}

/**
 * Write a number to a file descriptor in a certain base
 * @param n			The number to write
 * @param *base		The base of the number (ex.: "01234567890ABCDEF")
 * @param fd		The file descriptor to write to
 * @return			The amount of characters written, or -1 on error
 */
int	ft_putnbr_base_fd(unsigned int n, char *base, int fd)
{
	int		base_num;

	base_num = ft_strlen(base);
	if (!is_valid_base(base))
		return (0);
	if (n == 0)
		return (write(fd, base, 1));
	return (nbr_loop(n, base, base_num, fd));
}
