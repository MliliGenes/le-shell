/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 23:08:21 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/04/23 22:38:35 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void handle_cd(char *input, t_env_var *env_list)
{
    char **args;
    char *oldpwd;
    char *target_dir = NULL;
    int change_success = 0;
    
    args = ft_split(input, ' ');
    if (!args)
        return;
    oldpwd = getcwd(NULL, 0);
    if (!oldpwd)
    {
        ft_putstr_fd("cd: error getting current directory\n", 2);
        free_2d(args);
        return;
    }    
    if (ft_strcmp(args[0], "cd") == 0 && (!args[1] || ft_strcmp(args[1], "~") == 0))
    {
        target_dir = get_env_value(env_list, "HOME");
        if (!target_dir)
            ft_putstr_fd("cd: HOME not set\n", 2);
        else if (chdir(target_dir) == -1)
            ft_putstr_fd("cd: cannot access HOME directory\n", 2);
        else
            change_success = 1;
    }
    else if (ft_strcmp(args[0], "cd") == 0 && ft_strcmp(args[1], "-") == 0)
    {
        target_dir = get_env_value(env_list, "OLDPWD");
        if (!target_dir)
            ft_putstr_fd("cd: OLDPWD not set\n", 2);
        else if (chdir(target_dir) == -1)
            ft_putstr_fd("cd: cannot access OLDPWD directory\n", 2);
        else
        {
            printf("%s\n", target_dir);
            change_success = 1;
        }
    }
    else if (ft_strcmp(args[0], "cd") == 0 && args[1])
    {
        if (chdir(args[1]) == -1)
            cd_error(args[1]);
        else
            change_success = 1;
    }    
    if (change_success)
    {
        char *newpwd = getcwd(NULL, 0);
        if (newpwd)
        {
            env_update(env_list, "OLDPWD", oldpwd);
            env_update(env_list, "PWD", newpwd);
            free(newpwd);
        }
    }
    free(oldpwd);
    free_2d(args);
}
