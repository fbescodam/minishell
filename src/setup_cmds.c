int	parse_cmd(t_cmd *cmd, char *prompt)
{
	
}

t_list	*setup_cmds(t_mini *mini)
{
	t_cmd	*cmd;
	t_list	*cmd_instance;

	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->mini = mini;
	cmd_instance = ft_lstnew(cmd);
	if (!cmd_instance)
	{
		free(cmd);
		return(NULL);
	}
	if (!(mini->cmds))
		mini->cmds = cmd_instance;
	else
		ft_lstadd_back(mini->cmds, cmd_instance);
	return (cmd_instance);
}

int	setup_cmds(t_mini *mini)
{
	int	i;
	t_list	*current_cmd;
	i = 0;

	while (prompts[i])
	{
		current_cmd = new_cmd(mini);
		if (current_cmd == NULL)
				return(ENOMEM);
		if (i > 0)
			pipe_in(current_cmd->content, &fd);
		ret = parse_cmd(current_cmd, prompts[i]);
		if (ret != 0 && ret != -1)
			return (ret);
		if (commands[i + 1])
			pipe_out(current_cmd->content, &fd);
		i++;
	}
}
