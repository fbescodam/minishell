#include "include/custom_errors.h"
#include "libft/libft.h"

int		scan_operators(char *prompt, char *operators)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (prompt[i])
	{
		while (operators[k])
		{
			if (prompt[i] == operators[k])
				return (i);
			k++;
		}
		i++;
		k = 0;
	}
	return (i);
}

char	*skip_chars(char *prompt, char *mask_set)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (prompt[i])
	{
		while (mask_set[k])
		{
			if (prompt[i] == mask_set[k])
				k++;
			else 
				return (prompt + i);
		}
		i++;
		k = 0;
	}
	return (prompt + i);
	
}
