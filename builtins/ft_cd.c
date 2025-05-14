/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: le-saad <le-saad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 23:08:21 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/05/14 08:18:00 by le-saad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

static int	handle_home(t_env_var *env)
{
	char	*home;

	home = get_env_value(env, "HOME");
	if (!home)
	{
		print_cd_error(NULL, NULL, "HOME not set\n");
		return (0);
	}
	if (chdir(home) == -1)
	{
		print_cd_error(NULL, home, "cannot access HOME directory\n");
		return (0);
	}
	return (1);
}

static int	handle_oldpwd(t_env_var *env)
{
	char	*oldpwd;

	oldpwd = get_env_value(env, "OLDPWD");
	if (!oldpwd)
	{
		print_cd_error(NULL, NULL, "OLDPWD not set\n");
		return (0);
	}
	if (chdir(oldpwd) == -1)
	{
		print_cd_error(NULL, oldpwd, "cannot access OLDPWD directory\n");
		return (0);
	}
	ft_putendl_fd(oldpwd, STDOUT_FILENO);
	return (1);
}

int	handle_cd(char **args, t_env_var *env)
{
	char	*old_pwd;
	int		success;

	if (args[2] != NULL)
		return 1;
	old_pwd = getcwd(NULL, 0);
	success = 0;
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
		success = handle_home(env);
	else if (ft_strcmp(args[1], "-") == 0)
		success = handle_oldpwd(env);
	else if (chdir(args[1]) == -1)
	{
		print_cd_error(NULL, args[1], "No such file or directory\n");
		return 1;
	}
	else
		success = 1;
	if (success)
		update_pwd(env, old_pwd);
	free(old_pwd);
	return (0);
}
