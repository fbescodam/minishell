# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fbes <fbes@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2021/11/26 23:07:45 by fbes          #+#    #+#                  #
#    Updated: 2022/01/19 23:04:40 by fbes          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		minishell

SRCS =		main.c signal_handler.c redirection_utils.c setup.c tokenize.c \
			token_setup.c command_handler.c reserved_cmds.c char_array_utils.c \
			pipe.c builtins/exit.c builtins/cd.c builtins/pwd.c

HEADERS =	utils.h

INCLUDES =	-I lib/libft -I /Users/$(USER)/.brew/opt/readline/include

OBJS =		$(SRCS:.c=.o)

CFLAGS =

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS) libft/libft.a
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) -lreadline \
	-L /Users/$(USER)/.brew/opt/readline/lib libft/libft.a -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

libft/libft.a:
	make -C libft

bonus:
	@echo We did not do the bonus yet

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean:
	rm -f $(OBJS) $(NAME)
	make -C libft fclean

re: fclean all

brew:
	curl https://brew.42.fr/ | bash

readline:
	brew install readline
	brew link --force readline

.PHONY: all clean fclean re bonus readline brew
