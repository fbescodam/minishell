/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isprint.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 21:49:46 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:20:33 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * Check if an integer is a printable ASCII value
 * @param c		The integer to check
 * @return		Returns 1 if true, 0 if false
 */
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
