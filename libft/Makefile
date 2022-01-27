# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fbes <fbes@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2020/10/26 14:25:38 by fbes          #+#    #+#                  #
#    Updated: 2022/01/27 17:32:02 by fbes          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		libft.a

SRCS =		ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
			ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memccpy.c \
			ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
			ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
			ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c \
			ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
			ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
			ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
			ft_lstmap.c ft_putnbr_base_fd.c ft_putptr_fd.c ft_numlen.c \
			ft_ptrlen.c ft_abs.c ft_isneg.c ft_biggest.c ft_itoa_base.c \
			ft_ptoa.c ft_get_next_line.c ft_strnlen.c ft_free.c ft_realloc.c \
			ft_lstsort.c ft_iswhitespace.c ft_free_double_ptr.c ft_strclen.c \
			ft_lstget.c ft_smallest.c ft_strschr.c ft_strhash.c \
			ft_ditemnew.c ft_dlstadd_back.c ft_dlstadd_front.c ft_dlstclear.c \
			ft_dlstdelone.c ft_dlstget.c ft_dlstiter.c ft_dlstlast.c \
			ft_dlstmap.c ft_dlstnew.c ft_dlstrem.c

OBJS =		$(addprefix obj/,$(SRCS:.c=.o))

CFLAGS =	-Wall -Wextra -Werror -pedantic -std=c89

all: $(NAME)

obj/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

bonus: $(NAME)

clean:
	rm -rf obj

fclean:
	rm -rf obj $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
