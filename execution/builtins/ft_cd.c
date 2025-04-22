/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 23:08:21 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/04/22 01:47:19 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Feature         | Must implement?  | Why?
// cd ./dir        | ✅ Yes           | Relative path
// cd /dir         | ✅ Yes           | Absolute path
// cd .., cd .     | ⚠️ Optional       | Covered by relative logic
// cd alone / cd ~ | ❌ No            | Not required by subject
// cd -            | ❌ No            | Also not required

static void cd_error(char *path)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	handle_cd(char *input, t_env_var *env_list)
{
	char **args;
	char *oldpwd;
	char *newpwd;
	
	args = ft_split(input, ' ');
	if (!args)
		return ;
	if (ft_strcmp(args[0], "cd") == 0 && args[1])
	{
		oldpwd = getcwd(NULL, 0);
		if (chdir(args[1]) == -1)
		{
			cd_error(args[1]);
			free(oldpwd);
			free_2d(args);
			return ;
		}
		newpwd = getcwd(NULL, 0);
		env_update(env_list, "OLDPWD", oldpwd);
		env_update(env_list, "PWD", newpwd);
		free(oldpwd);
		free(newpwd);
	}
	free_2d(args);
}
