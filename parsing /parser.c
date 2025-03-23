#include "include/parsing.h"

int	fill_cmd_node(t_cmd_node *cmd_node, char *chunk)
{
	return (0);
}

t_cmd_node	*create_cmd_node(char *chunk)
{
	t_cmd_node	*cmd_node;

	cmd_node = malloc(sizeof(t_cmd_node));
	if (!cmd_node)
		return (NULL);
	cmd_node->cmd = NULL;
	cmd_node->args = NULL;
	cmd_node->redir = NULL;
	cmd_node->next = NULL;
	return (cmd_node);
}

t_cmd_node	*split_command_line(char *big_f_chunk)
{
	t_cmd_node	*head;

	return ;
}

int	main(void)
{
	char	*input;

	input = readline("le_shell> ");
	return (0);
}
