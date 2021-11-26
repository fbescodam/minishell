all:
	cd libft; make
	gcc main.c exit.c redirection_utils.c setup.c libft/libft.a -lreadline
