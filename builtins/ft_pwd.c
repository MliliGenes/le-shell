/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:34:31 by ssbaytri          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/06 16:25:43 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void	handle_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		printf("%s\n", pwd);
		free(pwd);
	}
	else
		perror("getcwd");
=======
/*   Updated: 2025/05/02 00:12:18 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_pwd(char *input)
{
	char	*pwd;

	if ((ft_strcmp(input, "pwd") == 0))
	{
		pwd = getcwd(NULL, 0);
		if (pwd)
			printf("%s\n", pwd);
		else
			perror("getcwd");
		free(pwd);
	}
>>>>>>> 592d8acb6f76f104019ec385ef186264a06f64cc
}
