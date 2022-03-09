NAME =		minishell

SRCS =		src/utils/debugging.c src/error_handling.c src/main.c src/setup.c \
			src/signal_handler.c src/utils/garbage.c src/envars/basics.c \
			src/envars/parser.c src/utils/strings.c src/envars/helpers.c \
			src/parsing/parse.c src/parsing/parse_utils.c \
			src/utils/char_array_utils.c src/parsing/parse_cmds.c \
			src/parsing/parse_redirections.c src/envars/set.c \
			src/parsing/parse_params.c src/exec/exec_list.c \
			src/exec/check_cmd.c src/exec/child.c src/exec/redirections.c \
			src/exec/reserved_cmds.c src/utils/builtin_utils.c \
			src/builtins/cd.c src/builtins/echo.c src/builtins/env.c \
			src/builtins/exit.c src/builtins/export.c src/builtins/pwd.c \
			src/builtins/unset.c src/parsing/read_input.c \
			src/parsing/get_next_line.c src/parsing/get_next_line_utils.c

INCLUDES =	-I includes -I libft -I /Users/$(USER)/.brew/opt/readline/include

OBJS =		$(subst src/,obj/,$(SRCS:.c=.o))

CFLAGS =	

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS) libft/libft.a
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) -lreadline \
	-L /Users/$(USER)/.brew/opt/readline/lib libft/libft.a -o $(NAME)

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

libft/libft.a:
	make -C libft

bonus:
	@echo We did not do the bonus yet

clean:
	rm -rf 'obj'
	make -C libft clean

fclean:
	rm -rf 'obj' '$(NAME)'
	make -C libft fclean

re: fclean all

brew:
	curl https://brew.42.fr/ | bash

readline:
	brew install readline
	brew link --force readline

.PHONY: all clean fclean re bonus readline brew
