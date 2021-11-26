/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_biggest.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/10 20:35:09 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:19:07 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * Return the biggest integer of two
 * @param a		An integer to compare with
 * @param b		Another integer to compare with
 * @return		The biggest of the two
 */
int	ft_biggest(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
