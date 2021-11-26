/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tolower.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 21:50:25 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:59:24 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * Change an uppercase letter to lowercase
 * @param c		The ASCII value to change to lowercase
 * @return		The ASCII value in uppercase
 */
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
