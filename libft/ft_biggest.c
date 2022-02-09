/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_biggest.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/10 20:35:09 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/08 19:48:05 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * Return the biggest integer of two
 * @param[in] a		An integer to compare with
 * @param[in] b		Another integer to compare with
 * @return		The biggest of the two
 */
int	ft_biggest(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
