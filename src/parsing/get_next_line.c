#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "libft.h"
#include <stdio.h>

int	sort_buffer(int fd, char *buff, int *curr_seg)
{
	static int	i = -1;
	int			res;

	if (i == -1)
	{
		res = read(fd, buff, 100);
		i++;
		if (res <= 0)
			return (res - 1);
		if (res < 100)
			buff[res] = 0;
	}
	*curr_seg = i;
	while (buff[i] != '\n' && buff[i])
		i++;
	if (buff[i] == '\n')
	{
		i++;
		return (1);
	}
	i = -1;
	return (0);
}

int	join_til_nl(char **line, char *temp, char *curr_seg)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	while (curr_seg[k] && curr_seg[k] != '\n')
		k++;
	line[0] = malloc(i + k + 1);
	if (!line[0])
		return (-1);
	i = 0;
	while (temp[i])
	{
		line[0][i] = temp[i];
		i++;
	}
	k = 0;
	while (curr_seg[k] && curr_seg[k] != '\n')
	{
		line[0][i + k] = curr_seg[k];
		k++;
	}
	return (i + k);
}

int	realloc_string(char **line, int index, char *buff)
{
	char	*temp;
	char	*curr_seg;
	int		res;

	temp = ft_strdup("");
	if (!temp)
		return (0);
	curr_seg = buff + index;
	if (*line)
	{
		free(temp);
		temp = ft_strdup(line[0]);
		free(line[0]);
		if (!temp)
			return (0);
	}
	res = join_til_nl(line, temp, curr_seg);
	free(temp);
	if (res < 0)
		return (0);
	line[0][res] = 0;
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	buff[101];
	int			res;
	int			current_segment;

	if (line == 0)
		return (gnl_reset(buff));
	buff[100] = 0;
	*line = 0;
	res = 0;
	while (res == 0)
	{
		res = sort_buffer(fd, buff, &current_segment);
		if (res == -1)
		{
			if (*line == 0)
				return (malloc_empty_string(line));
			return (0);
		}
		if (res == -2)
			return (-1);
		if (!realloc_string(line, current_segment, buff))
			return (-1);
	}
	return (1);
}
