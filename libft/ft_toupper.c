/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_toupper.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 20:53:28 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:59:39 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * Change an lowercase letter to uppercase
 * @param c		The ASCII value to change to uppercase
 * @return		The ASCII value in lowercase
 */
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
