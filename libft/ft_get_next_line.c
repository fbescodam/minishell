/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_next_line.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/11 15:30:52 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/01 21:20:09 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strnlen_nl(const char *s, size_t maxlen)
{
	size_t	i;

	i = 0;
	while (i < maxlen && s[i] != '\0' && s[i] != '\n')
		i++;
	return (i);
}

static void	ft_strlcpy_nl(char *dest, const char *src, size_t size)
{
	size_t	i;

	if (size != 0)
	{
		i = 0;
		while (i < size && src[i] != '\n')
		{
			dest[i] = src[i];
			i++;
		}
	}
}

static int	init_gnl(int fd, char **line, void **buff, ssize_t *read_bytes)
{
	if (fd < 0 || BUFFER_SIZE < 1 || line == NULL)
		return (-1);
	if (!*buff)
	{
		*buff = ft_calloc(sizeof(char), BUFFER_SIZE);
		if (!*buff)
			return (-1);
		*read_bytes = read(fd, *buff, BUFFER_SIZE);
	}
	*line = NULL;
	return (0);
}

static int	handle_buff(char **line, size_t *size,
				char *buff, size_t read_bytes)
{
	static size_t	start;
	char			*temp;
	size_t			bytes_to_copy;

	bytes_to_copy = ft_strnlen_nl(buff + start, read_bytes - start);
	temp = (char *)ft_calloc(sizeof(char), (*size + bytes_to_copy + 1));
	if (!temp)
		return (-1);
	if (*line)
	{
		ft_strlcpy_nl(temp, *line, *size);
		free(*line);
	}
	if (bytes_to_copy > 0)
		ft_strlcpy_nl(temp + *size, buff + start, bytes_to_copy);
	*line = temp;
	*size += bytes_to_copy;
	if (bytes_to_copy < read_bytes - start)
	{
		start += bytes_to_copy + 1;
		return (1);
	}
	ft_bzero(buff, BUFFER_SIZE);
	start = 0;
	return (0);
}

/**
 * Read from a file descriptor, line by line
 * @param fd		The file descriptor to read from
 * @param **line	A pointer to the string to inject the line into
 * @return			Returns 1 if there's more to read, 0 once the input has
 * 					been read entirely, -1 on error
 */
int	ft_get_next_line(int fd, char **line)
{
	static void		*buff;
	static ssize_t	read_bytes;
	size_t			size;
	int				handle_result;

	if (init_gnl(fd, line, &buff, &read_bytes) == -1)
		return (-1);
	size = 0;
	while (read_bytes > 0)
	{
		handle_result = handle_buff(line, &size, buff, read_bytes);
		if (handle_result > 0)
			return (1);
		else if (handle_result < 0)
			break ;
		read_bytes = read(fd, buff, BUFFER_SIZE);
	}
	if (!*line)
		*line = ft_calloc(sizeof(char), 1);
	ft_free(buff);
	if (read_bytes < 0 || handle_result < 0)
		return (-1);
	return (0);
}
