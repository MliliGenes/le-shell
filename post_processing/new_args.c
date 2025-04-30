/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:47:52 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/30 14:52:22 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*dup;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*ptr;

	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	ptr = (char *)malloc(len + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

void	free_args(char **args)
{
	if (!args)
		return ;
	for (int i = 0; args[i]; i++)
		free(args[i]);
	free(args);
}

// Helper to create test args
char	**create_test_args(const char *argv[], int argc)
{
	char	**args;

	args = calloc(argc + 1, sizeof(char *));
	if (!args)
		return (NULL);
	for (int i = 0; i < argc; i++)
	{
		args[i] = strdup(argv[i]);
		if (!args[i])
		{
			free_args(args);
			return (NULL);
		}
	}
	return (args);
}

bool	is_white_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	holy_count_words(char *str)
{
	bool	in_quote;
	bool	in_word;
	int		counter;
	int		index;

	counter = 0;
	index = 0;
	in_quote = 0;
	in_word = false;
	while (str && str[index])
	{
		if (str[index] == '\'' || str[index] == '"')
			in_quote = !in_quote;
		if (!is_white_space(str[index]) && !in_word)
		{
			in_word = true;
			counter++;
		}
		else if (!in_quote && in_word && is_white_space(str[index]))
			in_word = false;
		index++;
	}
	return (counter);
}

int	count_args_in_cmd(char **args)
{
	int	count;

	count = 0;
	if (!args)
		return (0);
	while (args[count])
		count++;
	return (count);
}

int	args_total_len(char **args)
{
	int	index;
	int	total;

	index = 0;
	total = 0;
	while (args && args[index])
	{
		total += ft_strlen(args[index]);
		index++;
	}
	return (total);
}

char	*holy_joint(char **args)
{
	char	*str;
	int		i[3];
	int		spaces;
	int		chars;

	spaces = count_args_in_cmd(args) - 1;
	chars = args_total_len(args);
	str = malloc(chars + spaces + 1);
	if (!str)
		return (NULL);
	i[2] = 0;
	i[0] = 0;
	while (args && args[i[0]])
	{
		i[1] = 0;
		while (args[i[0]][i[1]])
			str[i[2]++] = args[i[0]][i[1]++];
		if (i[0] < spaces)
			str[i[2]++] = ' ';
		i[0]++;
	}
	str[i[2]++] = 0;
	free_args(args);
	return (str);
}

char	**holy_split(char *joint)
{
	char	**new_args;
	int		index;
	int		start;
	int		end;
	bool	in_quote;

	start = 0;
	end = 0;
	index = 0;
	in_quote = false;
	new_args = malloc(sizeof(char *) * (holy_count_words(joint) + 1));
	if (!new_args)
		return (NULL);
	while (index < holy_count_words(joint))
	{
		while (joint[end] && (is_white_space(joint[end]) && !in_quote))
			end++;
		start = end;
		while (joint[end] && (!is_white_space(joint[end]) || in_quote))
		{
			if (joint[end] == '\'' || joint[end] == '"')
				in_quote = !in_quote;
			end++;
		}
		new_args[index] = ft_substr(joint, start, end - start);
		if (!new_args[index])
		{
			free_args(new_args);
			return (NULL);
		}
		index++;
	}
	new_args[index] = NULL;
	return (new_args);
}


// int	main(void)
// {
// 	// Test Case 1: Normal arguments
// 	{
// 		const char *argv[] = {"hello", "world", "42", NULL};
// 		char **args = create_test_args(argv, 3);
// 		char *result = holy_joint(args);
// 		printf("Test 1: Normal args\n");
// 		printf("Input: {\"hello\", \"world\", \"42\"}\n");
// 		printf("Output: \"%s\"\n", result);
// 		printf("Expected: \"helloworld42\"\n\n");
// 		free(result);
// 		free_args(args);
// 	}

// 	// Test Case 2: Single argument
// 	{
// 		const char *argv[] = {"minishell", NULL};
// 		char **args = create_test_args(argv, 1);
// 		char *result = holy_joint(args);
// 		printf("Test 2: Single arg\n");
// 		printf("Input: {\"minishell\"}\n");
// 		printf("Output: \"%s\"\n", result);
// 		printf("Expected: \"minishell\"\n\n");
// 		free(result);
// 		free_args(args);
// 	}

// 	// Test Case 3: Empty args (NULL-terminated empty array)
// 	{
// 		char **args = calloc(1, sizeof(char *)); // {NULL}
// 		char *result = holy_joint(args);
// 		printf("Test 3: Empty args\n");
// 		printf("Input: {NULL}\n");
// 		printf("Output: \"%s\"\n", result ? result : "(NULL)");
// 		printf("Expected: \"\" (empty string)\n\n");
// 		free(result);
// 		free_args(args);
// 	}

// 	// Test Case 4: NULL input
// 	{
// 		char *result = holy_joint(NULL);
// 		printf("Test 4: NULL input\n");
// 		printf("Input: NULL\n");
// 		printf("Output: \"%s\"\n", result ? result : "(NULL)");
// 		printf("Expected: NULL or \"\" (implementation-dependent)\n\n");
// 		free(result);
// 	}

// 	return (0);
// }

void	update_quote_status(char c, bool *in_single, bool *in_double)
{
	if (c == '\'' && !(*in_double))
		*in_single = !(*in_single);
	else if (c == '"' && !(*in_single))
		*in_double = !(*in_double);
}

bool	is_in_quote(bool in_single, bool in_double)
{
	return (in_single || in_double);
}

int	holy_count_words(char *str)
{
	bool	in_single_quote;
	bool	in_double_quote;
	bool	in_word;
	int		counter;
	int		index;

	counter = 0;
	index = 0;
	in_single_quote = false;
	in_double_quote = false;
	in_word = false;
	while (str && str[index])
	{
		update_quote_status(str[index], &in_single_quote, &in_double_quote);
		if (!is_white_space(str[index]) && !in_word)
		{
			in_word = true;
			counter++;
		}
		else if (!is_in_quote(in_single_quote, in_double_quote) && 
				in_word && is_white_space(str[index]))
			in_word = false;
		index++;
	}
	return (counter);
}

int	find_word_start(char *joint, int end, bool *in_single, bool *in_double)
{
	while (joint[end] && is_white_space(joint[end]) && 
		!is_in_quote(*in_single, *in_double))
		end++;
	return (end);
}

int	find_word_end(char *joint, int end, bool *in_single, bool *in_double)
{
	while (joint[end] && (!is_white_space(joint[end]) || 
		is_in_quote(*in_single, *in_double)))
	{
		update_quote_status(joint[end], in_single, in_double);
		end++;
	}
	return (end);
}

char	**holy_split(char *joint)
{
	char	**new_args;
	int		index, start, end;
	bool	in_single_quote, in_double_quote;

	start = 0;
	end = 0;
	index = 0;
	in_single_quote = false;
	in_double_quote = false;
	new_args = malloc(sizeof(char *) * (holy_count_words(joint) + 1));
	if (!new_args)
		return (NULL);
	while (index < holy_count_words(joint))
	{
		end = find_word_start(joint, end, &in_single_quote, &in_double_quote);
		start = end;
		end = find_word_end(joint, end, &in_single_quote, &in_double_quote);
		new_args[index] = ft_substr(joint, start, end - start);
		if (!new_args[index])
		{
			free_args(new_args);
			return (NULL);
		}
		index++;
	}
	new_args[index] = NULL;
	return (new_args);
}