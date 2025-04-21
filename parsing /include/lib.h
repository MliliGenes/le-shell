/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: le-saad <le-saad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 08:48:06 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/21 23:16:37 by le-saad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include "dependencies.h"
# include "structs.h"

size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strdup(const char *s);
char		*ft_strndup(const char *s, size_t n);

const char	*token_type_name(t_token_type type);
void		print_tokens(t_token *head);
void		print_ready_tokens(t_ready_token *head);
void        print_ast_stylish(t_ast *root);

#endif