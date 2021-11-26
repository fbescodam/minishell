/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_abs.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/02 20:02:21 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:18:36 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * Get the absolute value of a number
 * @param n		The number to get the absolute value of
 * @return		The absolute number
 */
unsigned int	ft_abs(int n)
{
	if (n == -2147483648)
		return (2147483648);
	if (n < 0)
		return ((unsigned int) - n);
	return ((unsigned int)n);
}
