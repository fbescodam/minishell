/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_numlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/02 19:31:44 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:24:08 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * Get the amount of digits in a number of a certain base
 * @param n			The number to check the amount of digits of
 * @param base		The base the number is in (usually 10)
 * @return			The amount of digits in the number in that base
 */
int	ft_numlen(unsigned long n, unsigned int base)
{
	if (n < base)
		return (1);
	return (1 + ft_numlen(n / base, base));
}
