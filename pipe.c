int		setup_pipe(t_list **tokens)
{
	t_cmd *cmd;

	cmd = (cmd *)malloc (sizeof(t_cmd));
	int fd[2] = pipe();
	//add token with content fd[2] and flag pipe in
	cmd->tokens = *tokens;
	//execute command
	//free command
	*tokens = ft_lstnew(//add token with fd[2] and flag pipe out)
	//return to tokenizing next command
}
