/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:35:10 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/05/07 21:49:46 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "dependencies.h"
# include "lib.h"
# include "structs.h"
# include "builtins.h"

char	*get_cmd_path(t_cmd *cmd, char **paths);
char	**env_to_array(t_env_var *env);

#endif