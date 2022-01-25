#include "structs.h"
// #include "tokens.h"
#include "../libft/libft.h"

/**
 * @brief Free a token struct. The contents are not freed if flag is CMD, as
 * then the contents were freed in free_cmd (contents is then a reference to
 * the params pointer in the t_cmd struct).
 *
 * @param token the token to free
 */
void	free_token(void *token)
{
	if (!token)
		return ;
	if (((t_token *)token)->flag != 1)			// TODO: change to CMD
		ft_free(((t_token *)token)->content);
	ft_free(token);
}

void	free_cmd(void *cmd)
{
	if (!cmd)
		return ;
	ft_free_double_ptr((void **)((t_cmd *)cmd)->params);
	ft_lstclear(&((t_cmd *)cmd)->tokens, &free_token);
	ft_free(((t_cmd *)cmd)->path);
	ft_free(cmd);
}

void	free_envar(void *envar)
{
	return ;			// TODO: free envars after reimplementing them
	if (!envar)
		return ;
	ft_free(((t_envar *)envar)->name);
	ft_free(((t_envar *)envar)->val);
	ft_free(envar);
}

void	free_mini(t_mini *mini)
{
	if (!mini)
		return ;
	if (mini->envars)
		ft_lstclear(&mini->envars, &free_envar);
	if (mini->cmds)
		ft_lstclear(&mini->cmds, &free_cmd);
	ft_free_double_ptr((void **)mini->paths);
}
