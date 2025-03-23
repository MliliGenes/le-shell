#include "include/parsing.h"

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

int	is_and_op(char *src)
{
	return ((src[0] == '&' && src[1] == '&'));
}

int	is_or_op(char *src)
{
	return ((src[0] == '&' && src[1] == '&'));
}

int	is_pipe_op(char *src)
{
	return ((src[0] == '&' && src[1] == '&'));
}

t_cmd_node	*split_command_line(char *big_f_chunk)
{
	t_cmd_node	*head;
	int			index;
	int			start;
	char		*cmd;

	head = NULL;
	index = 0;
	start = 0;
	while (big_f_chunk[index])
	{
		if (is_pipe_op(&big_f_chunk[index]) || is_and_op(&big_f_chunk[index])
			|| is_or_op(&big_f_chunk[index]))
		{
			cmd = ft_strndup(&big_f_chunk[start], index - start);
			printf("%s\n", cmd);
			if (is_and_op(&big_f_chunk[index]) || is_or_op(&big_f_chunk[index]))
				index += 2;
			else
				index++;
			start = index;
		}
		index++;
	}
	if (start < index)
	{
		cmd = ft_strndup(&big_f_chunk[start], index - start);
		printf("%s\n", cmd);
	}
	return (head);
}

int	main(void)
{
	char	*input;

	input = "ls -l | lol";
	split_command_line(input);
	return (0);
}
