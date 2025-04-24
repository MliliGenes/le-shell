/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dependencies.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: le-saad <le-saad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 08:49:15 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/24 17:45:52 by le-saad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEPENDENCIES_H
# define DEPENDENCIES_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>

# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
# define BOLDWHITE "\033[1m\033[37m"

# define REDIR_NEEDS_TARGET "Redirection needs target file"
# define CONSECUTIVE_OPS "Consecutive operators not allowed"
# define CHAINED_REDIRS "Can't chain redirections"
# define INVALID_AFTER_PAREN "Invalid token after parenthesis"
# define INVALID_SEQUENCE "Invalid token sequence"
# define MISPLACED_PAREN "Misplaced parenthesis"
# define PIPE_CONNECT "Pipe must connect commands"
# define UNBALANCED_QUOTES "Unbalanced quotes in command"
# define UNBALANCED_PARENS "Unbalanced parentheses in command"

#endif