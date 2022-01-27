NAME =		minishell

SRCS =		src/utils/debugging.c src/error_handling.c src/main.c src/setup.c \
			src/signal_handler.c src/utils/garbage.c src/envars/basics.c \
			src/envars/parser.c src/utils/strings.c src/envars/helpers.c \
			src/parse.c src/parse_utils.c src/utils/char_array_utils.c

INCLUDES =	-I includes -I libft -I /Users/$(USER)/.brew/opt/readline/include

OBJS_F =	$(SRCS:.c=.o)

OBJS =		$(subst src/,obj/,$(OBJS_F))

CFLAGS =

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS) libft/libft.a
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) -lreadline \
	-L /Users/$(USER)/.brew/opt/readline/lib libft/libft.a -o $(NAME) -fsanitize=address

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
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
