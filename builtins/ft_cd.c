/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 23:08:21 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/05/06 16:36:58 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

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

void    handle_cd(char **args, t_env_var *env)
{
    char *old_pwd = getcwd(NULL, 0);
    int change_success = 0;

    if (!args[1] || ft_strcmp(args[1], "~") == 0)
    {
        char *home = get_env_value(env, "HOME");
        if (!home)
            ft_putstr_fd("cd: HOME not set\n", 2);
        else if (chdir(home) == -1)
			ft_putstr_fd("cd: cannot access HOME directory\n", 2);
		else
			change_success = 1;
    }
    else if (ft_strcmp(args[1], "-") == 0)
    {
        char *old = get_env_value(env, "OLDPWD");
        if (!old)
            ft_putstr_fd("cd: OLDPWD not set\n", 2);
        else if (chdir(old) == -1)
			ft_putstr_fd("cd: cannot access OLDPWD directory\n", 2);
        else
        {
            printf("%s\n", old);
            change_success = 1;
        }
    }
    else if (chdir(args[1]) == -1)
        cd_error(args[1]);
    else
        change_success = 1;
    if (change_success)
    {
        char *new_pwd = getcwd(NULL, 0);
        if (new_pwd)
        {
            env_update(env, "OLDPWD", old_pwd);
            env_update(env, "PWD", new_pwd);
            free(new_pwd);
        }
    }
    free(old_pwd);
}
