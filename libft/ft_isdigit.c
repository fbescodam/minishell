/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isdigit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 21:49:10 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:20:26 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * Check if an integer is an numeric ASCII value
 * @param c		The integer to check
 * @return		Returns 1 if true, 0 if false
 */
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
