# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fbes <fbes@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2021/11/26 23:07:45 by fbes          #+#    #+#                  #
#    Updated: 2021/12/03 22:10:00 by jgalloni      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		minishell

SRCS =		main.c exit.c redirection_utils.c setup.c tokenize.c token_setup.c command_handler.c

HEADERS =	utils.h

INCLUDES =	-I lib/libft -I /Users/$(USER)/.brew/opt/readline/include

OBJS =		$(SRCS:.c=.o)

CFLAGS = -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS) libft/libft.a
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) -lreadline -L /Users/$(USER)/.brew/opt/readline/lib libft/libft.a -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

libft/libft.a:
	make -C libft

bonus:
	@echo We did not do the bonus

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean:
	rm -f $(OBJS) $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re bonus
