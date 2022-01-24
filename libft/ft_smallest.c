/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_smallest.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 16:51:23 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/24 16:51:39 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * Return the smallest integer of two
 * @param a		An integer to compare with
 * @param b		Another integer to compare with
 * @return		The smallest of the two
 */
int	ft_smallest(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
