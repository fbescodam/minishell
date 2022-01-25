NAME =		minishell

SRCS =		debug_utils.c error_handling.c main.c setup.c signal_handler.c

INCLUDES =	-I includes -I lib/libft -I /Users/$(USER)/.brew/opt/readline/include

OBJS =		$(SRCS:.c=.o)

CFLAGS =

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS) libft/libft.a
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) -lreadline \
	-L /Users/$(USER)/.brew/opt/readline/lib libft/libft.a -o $(NAME) -fsanitize=address

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
