/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 23:08:21 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/04/21 02:01:27 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Feature         | Must implement?  | Why?
// cd ./dir        | ✅ Yes           | Relative path
// cd /dir         | ✅ Yes           | Absolute path
// cd .., cd .     | ⚠️ Optional       | Covered by relative logic
// cd alone / cd ~ | ❌ No            | Not required by subject
// cd -            | ❌ No            | Also not required

void	ft_cd(char *input, t_env_var *env_list)
{
	
}