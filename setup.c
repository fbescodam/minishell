#include <stdlib.h>
#include "libft/libft.h"

char	*check_command(char *command, char **paths)
{
	char	*new_path;
	char	*temp;
	int		i;

	i = 0;
	if (access(command, R_OK) == 0)
		return (command);
	temp = ft_strjoin("/", command);
	while (paths[i])
	{
		new_path = ft_strjoin(paths[i], temp);
		if (new_path && access(new_path, R_OK) == 0)
		{
			free(temp);
			return (new_path);
		}
		free(new_path);
		i++;
	}
	free(temp);
	return (0);
}

char	**set_path()
{
	char	*env;
	char	**paths;


	env = getenv("PATH");
	paths = ft_split(env, ':');
	//protect this laterrrr
	return (paths);
}
