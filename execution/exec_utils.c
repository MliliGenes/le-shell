/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:34:57 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/05/07 21:51:58 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

char	*get_cmd_path(t_cmd *cmd, char **paths)
{
	char	*tmp;
	char	*full_path;

	if (access(cmd->cmd, F_OK) == 0 && access(cmd->cmd, X_OK) == 0)
		return (ft_strdup(cmd->cmd));
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		full_path = ft_strjoin(tmp, cmd->cmd);
		free(tmp);
		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		paths++;
	}
	return (NULL);
}

static int	count_nodes(t_env_var *env)
{
	int			count;
	t_env_var	*tmp;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

static char	*join_key_value(t_env_var *env)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(env->key, "=");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, env->value);
	free(tmp);
	return (result);
}

char	**env_to_array(t_env_var *env)
{
	int			count;
	t_env_var	*tmp;
	char		**arr;

	count = count_nodes(env);
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	tmp = env;
	count = 0;
	while (tmp)
	{
		if (tmp->value)
			arr[count] = join_key_value(tmp);
		else
			arr[count] = ft_strdup(tmp->key);
		if (!arr[count])
		{
			free_2d(arr);
			return (NULL);
		}
		count++;
		tmp = tmp->next;
	}
	return (arr[count] = NULL, arr);
}
