/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 17:10:08 by fbes          #+#    #+#                 */
/*   Updated: 2022/01/24 17:11:22 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libft/libft.h"

typedef struct s_token {
	void		*content;
	int			flag;
}				t_token;

typedef struct s_envar
{
	char	*name;
	char	*val;
}			t_envar;

typedef struct s_mini
{
	t_list	*envars;
	char	**paths;
}			t_mini;

typedef struct s_cmd
{
	t_mini	*mini;
	char	*in_file;
	char	*out_file;
	int		in_fd;
	int		out_fd;
	int		mode;
	char	**params;
	char	*path;
	t_list	*tokens;
	int		argc;
}				t_cmd;

#endif
