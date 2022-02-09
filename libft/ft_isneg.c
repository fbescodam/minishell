/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isneg.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/02 20:09:11 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/08 19:48:05 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * Checks if an integer is negative (I know, I know, it can be useful though)
 * @param[in] n		The number to check
 * @return		Returns 1 if n is negative, 0 if not
 */
int	ft_isneg(int n)
{
	if (n < 0)
		return (1);
	return (0);
}
