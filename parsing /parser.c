#include "include/structs.h"

// int fill_cmd_node()
// {

// }

t_cmd_node	*create_cmd_node(char *chunk)
{
	t_cmd_node	*cmd_node;

	cmd_node = malloc(sizeof(t_cmd_node));
	if (!cmd_node)
		return (NULL);
	cmd_node->cmd = NULL;
	cmd_node->args = NULL;
	cmd_node->redir = NULL;
	return (cmd_node);
}

int	count_cmds_chunks(char *big_f_chunk)
{
	int		count;
	char	c;
	int		i;

	i = 0;
	count = 0;
	if (!big_f_chunk || !*big_f_chunk)
		return (-1);
	while (big_f_chunk[i])
	{

		i++;
	}
	return (count);
}

char	**split_command_line(char *big_f_chunk)
{
	return ;
}

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("minishell> ");
		if (*input)
		{
			add_history(input);
			printf("%s\n", input);
		}
	}
	return (0);
}
