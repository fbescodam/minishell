/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jgalloni <jgalloni@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 22:08:44 by jgalloni      #+#    #+#                 */
/*   Updated: 2022/04/18 16:49:28 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libft.h"

# define OUT_FILE 1
# define IN_FILE 2
# define HEREDOC 3
# define OUT_FILE_APPEND 4
# define PIPE_IN 5
# define PIPE_OUT 6

// global process id
int	g_pid;

typedef struct s_token {
	void		*content;
	int			flag;
	int			fd;
}				t_token;

typedef struct s_envar
{
	unsigned int	hash;
	char			*name;
	char			*val;
	char			*export;
}			t_envar;

typedef struct s_mini
{
	char	*prompt;
	t_dlist	*envars;
	char	**paths;
	t_list	*cmds;
	int		status;
}			t_mini;

typedef struct s_cmd
{
	t_mini	*mini;
	char	*heredoc;
	char	**params;
	int		pid;
	int		pipe_in[2];
	int		pipe_out[2];
	char	*path;
	int		builtin;
	t_list	*tokens;
}				t_cmd;

#endif
