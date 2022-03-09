/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jgalloni <jgalloni@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/02 17:50:29 by jgalloni      #+#    #+#                 */
/*   Updated: 2022/03/09 14:47:01 by jgalloni      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>

int		get_next_line(int fd, char **line);
int		realloc_string(char **line, int index, char *buff);
int		join_til_nl(char **line, char *temp, char *curr_seg);
int		sort_buffer(int fd, char *buff, int *curr_seg);
int		malloc_empty_string(char **str);

#endif
