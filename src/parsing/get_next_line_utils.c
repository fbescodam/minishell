#include <stdlib.h>
#include "libft.h"

int	malloc_empty_string(char **str)
{
	*str = ft_strdup("");
	if (!*str)
		return (-1);
	else
		return (0);
}
