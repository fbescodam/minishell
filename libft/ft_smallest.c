/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_smallest.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 16:51:23 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/08 19:48:05 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * Return the smallest integer of two
 * @param[in] a		An integer to compare with
 * @param[in] b		Another integer to compare with
 * @return		The smallest of the two
 */
int	ft_smallest(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
