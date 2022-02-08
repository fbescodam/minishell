/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_iswhitespace.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/19 10:55:23 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/08 19:48:05 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * Check if an integer is a whitespace ASCII value
 * @param[in] c		The integer to check
 * @return		Returns 1 if true, 0 if false
 */
int	ft_iswhitespace(char c)
{
	if (
		c == ' '
		|| c == '\f'
		|| c == '\n'
		|| c == '\r'
		|| c == '\t'
		|| c == '\v')
	{
		return (1);
	}
	return (0);
}
