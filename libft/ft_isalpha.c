/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalpha.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 21:48:56 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:20:17 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * Check if an integer is an alphabetical ASCII value
 * @param c		The integer to check
 * @return		Returns 1 if true, 0 if false
 */
int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
