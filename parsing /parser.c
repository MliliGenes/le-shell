#include "include/parsing.h"

// int	locate_redirection(char *chunk)
// {
// 	int	index;

// 	index = 0;
// 	while (chunk[index])
// 	{
// 		if (is_redir_in(&chunk[index]) || is_redir_out(&chunk[index])
// 			|| is_redir_her(&chunk[index]) || is_redir_append(&chunk[index]))
// 		{
// 		}
// 		else
// 			index++;
// 	}
// }

// int	fill_cmd_node(t_cmd_node *cmd_node, char *chunk)
// {

// 	return (0);
// }

t_cmd_node	*create_cmd_node(void)
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

static int	skip_ops(int *index, char *big_f_chunk)
{
	if (is_and_op(&big_f_chunk[*index]) || is_or_op(&big_f_chunk[*index]))
		(*index) += 2;
	else
		(*index)++;
	return (*index);
}

t_cmd_node	*split_command_line(char *big_f_chunk)
{
	int		index;
	int		start;
	char	*cmd;

	index = 0;
	start = 0;
	if (!big_f_chunk || !*big_f_chunk)
		return (NULL);
	while (1)
	{
		if (is_pipe_op(&big_f_chunk[index]) || is_and_op(&big_f_chunk[index])
			|| is_or_op(&big_f_chunk[index]))
		{
			if (index > start)
			{
				cmd = ft_strndup(&big_f_chunk[start], index - start);
				printf("command chunk: %s\n", cmd);
			}
			if (!big_f_chunk[index])
				break ;
			start = skip_ops(&index, big_f_chunk);
		}
		else
			index++;
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	split_command_line("    jhh ghj\"|\" hjghjgh");
	return (0);
}
