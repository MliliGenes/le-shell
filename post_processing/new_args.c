/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: le-saad <le-saad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:47:52 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/04 14:59:29 by le-saad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	holy_count_words(char *str)
{
	bool	in_s_q;	
	bool	in_d_q;
	bool	in_word;
	int		counter;
	int		index;

	counter = 0;
	index = 0;
	in_s_q = false;
	in_d_q = false;
	in_word = false;
	while (str && str[index])
	{
		update_quote_status(str[index], &in_s_q, &in_d_q);
		if (!is_white_space(str[index]) && !in_word)
		{
			in_word = true;
			counter++;
		}
		else if (!is_in_quote(in_s_q, in_d_q) && in_word
			&& is_white_space(str[index]))
			in_word = false;
		index++;
	}
	return (counter);
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
	return (str);
}

static void	*check(char **new_args, int i)
{
	if (!new_args[i])
	{
		while (i-- > 0)
		{
			free(new_args[i]);
		}
		free(new_args);
		return (NULL);
	}
}

char	**holy_split(char *joint)
{
	char	**new_args;
	int		i[3];
	bool	in_s_q;
	bool	in_d_q;

	i[1] = 0;
	i[2] = 0;
	i[0] = 0;
	in_s_q = false;
	in_d_q = false;
	new_args = malloc(sizeof(char *) * (holy_count_words(joint) + 1));
	if (!new_args)
		return (NULL);
	while (i[0] < holy_count_words(joint))
	{
		i[2] = find_word_start(joint, i[2], &in_s_q, &in_d_q);
		i[1] = i[2];
		i[2] = find_word_end(joint, i[2], &in_s_q, &in_d_q);
		new_args[i[0]] = ft_substr(joint, i[1], i[2] - i[1]);
		check(new_args, i[0]);
		i[0]++;
	}
	new_args[i[0]] = NULL;
	return (new_args);
}
