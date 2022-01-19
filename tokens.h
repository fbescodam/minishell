#ifndef TOKENS_H
# define TOKENS_H

# define CMD 1
# define INPUT_REDIR 2
# define OUTPUT_REDIR 3
# define INPUT_REDIR_APPEND 4
# define OUTPUT_REDIR_APPEND 5
# define PIPE_IN 6
# define PIPE_OUT 7

typedef struct s_token {
	void		*content;
	int			flag;
}				t_token;

int				tokenize(char *prompt, t_list **tokens);
int				setup_operator_token(t_list **tokens, int flag, char *pos, int *i);
int				setup_word_token(t_list **tokens, char **words);
int				setup_pipe(t_list **tokens);
void			free_token(void *token);

#endif
