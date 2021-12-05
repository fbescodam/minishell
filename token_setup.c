#include "libft/libft.h"
#include "tokens.h"
#include <stdio.h>

int	setup_operator_token(t_list **tokens, int flag)
{
	t_token	*new;
	t_list	*new_instance;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (-1);
	new->flag = flag;
	if (!(*tokens))
	{
		*tokens = ft_lstnew(new);
		if (!(*tokens))
			return (-1);
	}
	else
	{
		new_instance = ft_lstnew(new);
		if (!new_instance)
			return (-1);
		ft_lstadd_back(tokens, new_instance);
	}
	return (1);
}

int	setup_word_token(t_list **tokens, char *words)
{
	t_token	*new;
	t_list	*new_instance;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (-1);
	new->flag = WORD;
	new->word = words;
	if (!(*tokens))
	{
		*tokens = ft_lstnew(new);
		if (!(*tokens))
			return (-1);
	}
	else
	{
		new_instance = ft_lstnew(new);
		if (!new_instance)
			return (-1);
		ft_lstadd_back(tokens, new_instance);
	}
	return (1);
}

