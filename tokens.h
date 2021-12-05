#ifndef TOKENS_H
# define TOKENS_H

typedef struct token{

char	*word;
int		flag;

}t_token;

int		tokenize(char *prompt, t_list **tokens);
int	setup_operator_token(t_list **tokens, int flag);
int	setup_word_token(t_list **tokens, char *words);


#define WORD 1
#define INPUT_REDIR 2
#define OUTPUT_REDIR 3
#define INPUT_REDIR_APPEND 4
#define OUTPUT_REDIR_APPEND 5
#define PIPE 6

#endif
