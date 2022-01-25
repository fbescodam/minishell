#include <signal.h>
#include "custom_errors.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "readline/readline.h"

/**
  * @brief Handle signals
  * SIGINT is ctrl c
  * -1 is passed in case of EOF
  */
void	sig_handler(int sig)
{
	// system("leaks minishell");
	if (sig == 137)		// why 137?
	{
		write(2, "\nOut of memory\n", 15);		// TODO replace with our custom fd_putstring function
		exit(ENOMEM);
	}
	else if (sig == SIGINT)
	{
		printf("\n"); // Move to a new line
		rl_replace_line("", 0); // Clear the previous text
		printf("\x1b[1A\033[11C\x1b[0K\n");
		// Hooray for ANSI Escape Sequences!
		// \x1b stands for the ESCAPE key, then [1A goes up one line ([2A would go up two lines)
		// then [12C moves the cursor 12 places to the right
		// [0K removes all character from that position til the end of the line in the terminal
		rl_on_new_line(); // Regenerate the prompt on a newline
		rl_redisplay();
	}
}
