#include "include/structs.h"
#include <stdio.h>


void	print_char_array(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		printf("STR:%s:\n", arr[i]);
		i++;
	}
}
