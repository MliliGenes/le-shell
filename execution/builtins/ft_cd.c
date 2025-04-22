/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 23:08:21 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/04/22 22:33:27 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Feature         | Must implement?  | Why?
// cd ./dir        | ✅ Yes           | Relative path
// cd /dir         | ✅ Yes           | Absolute path
// cd .., cd .     | ⚠️ Optional       | Covered by relative logic
// cd alone / cd ~ | ❌ No            | Not required by subject
// cd -            | ❌ No            | Also not required

char *get_env_value(t_env_var *env_list, char *key)
{
	t_env_var *current = env_list;

	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return current->value;
		current = current->next;
	}
	return NULL;
}

static void cd_error(char *path)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

char	*advanced_cd(char **args, t_env_var *env_list)
{
	char *path;
	
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		char *home;
		
		home = get_env_value(env_list, "HOME");
		if (!home)
			return (ft_putstr_fd("cd: HOME not set\n", 2), NULL);
		path = home;
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		char *oldpwd;

		oldpwd = get_env_value(env_list, "OLDPWD");
		if (!oldpwd)
			return (ft_putstr_fd("cd: OLDPWD not set\n", 2), NULL);
		printf("%s\n", oldpwd);
		path = oldpwd;
	}
	else
		path = args[1];
	return path;
}

void	handle_cd(char *input, t_env_var *env_list)
{
	char **args;
	char *path;
	char *oldpwd;
	char *newpwd;
	
	args = ft_split(input, ' ');
	if (!args)
		return ;
	path = advanced_cd(args, env_list);
	if (!path)
		return (free_2d(args));
	oldpwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		cd_error(path);
		free(oldpwd);
	}
	else
	{
		newpwd = getcwd(NULL, 0);
		env_update(env_list, "OLDPWD", oldpwd);
		env_update(env_list, "PWD", newpwd);
		free(newpwd);
	}
	free(oldpwd);
	free_2d(args);
}
