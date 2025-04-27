/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 01:35:21 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/04/27 01:52:50 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// function expand_wildcards(args):
//     for each argument in args:
//         if '*' is found in the argument:
//             matches = []  // Initialize an empty list for matches

//             // Open current directory
//             dir = opendir(".")

//             if dir is NULL:
//                 print error("Cannot open current directory")
//                 return original args

//             // Read directory contents and find matches
//             for each file in dir:
//                 if file matches pattern (using wildcard_match function):
//                     add file to matches list

//             // If matches are found, replace the argument with the matches
//             if matches are not empty:
//                 replace the argument with matches list
//             else:
//                 leave the argument as is (or handle no matches error)

//             // Close directory after reading
//             closedir(dir)

//     return updated args


void handle_wildcards(char *input)
{
	char **args;
	int i;

	i = 1;
	args = ft_split(input, ' ');
	if (!args)
		return;
	while (args[i])
	{
		if (ft_strchr(args[i], '*'))
			expand_wildcards(&args[i]);
		i++;			
	}
	free_2d(args);
}