#ifndef STRUCTS_H
# define STRUCTS_H

# include "libft.h"

# define OUT_FILE 1
# define IN_FILE 2
# define IN_FILE_APPEND 3
# define OUT_FILE_APPEND 4
# define PIPE_IN 5
# define PIPE_OUT 6

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
	int				export;
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
	char	*in_file;
	char	*out_file;
	char	*heredoc;
	char	**params;
	int		pid;
	int		pipe_in[2];
	int		pipe_out[2];
	char	*path;
	t_list	*tokens;
	int		argc;
	t_list	*frake_err;
}				t_cmd;

#endif
