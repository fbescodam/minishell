#include "libft/libft.h"
#include "tokens.h"
#include <stdio.h>
#include <errno.h>
#include "custom_errors.h"

char	*next_word(char *str, int *i)
{
	int	j;
	int	start;

	j = 0;
	while (str[j] == ' ')
	{
		*i = *i + 1;
		j++;
	}
	if (str[j] == '<' || str[j] == '>' || str[j] == '|')
		return (0);
	start = j;
	while (str[j])
	{
		if (str[j] == '<' || str[j] == '>' || str[j] == '|' || str[j] == ' ')
			break ;
		*i = *i + 1;
		j++;
	}
	if (j - start > 0)
		return (ft_substr(str, start, j - start));
	return (0);
}

int	setup_operator_token(t_list **tokens, int flag, char *pos, int *i)
{
	t_token	*new;
	t_list	*new_instance;

	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new)
		return (ENOMEM);
	new->flag = flag;
	new->content = next_word(pos + 1, i);
	if (!(new->content))
		return (PARSE_ERROR); // parse error
	if (!(*tokens))
	{
		*tokens = ft_lstnew(new);
		if (!(*tokens))
			return (ENOMEM);
	}
	else
	{
		new_instance = ft_lstnew(new);
		if (!new_instance)
			return (ENOMEM);
		ft_lstadd_back(tokens, new_instance);
	}
	return (0);
}

int	setup_word_token(t_list **tokens, char **words)
{
	t_token	*new;
	t_list	*new_instance;

	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new)
		return (ENOMEM);
	new->flag = CMD;
	new->content = words;
	if (!(*tokens))
	{
		*tokens = ft_lstnew(new);
		if (!(*tokens))
			return (ENOMEM);
	}
	else
	{
		new_instance = ft_lstnew(new);
		if (!new_instance)
			return (ENOMEM);
		ft_lstadd_back(tokens, new_instance);
	}
	return (0);
}

