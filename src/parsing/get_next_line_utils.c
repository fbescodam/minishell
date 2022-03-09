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

int	gnl_reset(char *buff)
{
	ft_bzero(buff, 100);
	return (0);
}
