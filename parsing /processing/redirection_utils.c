/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: le-saad <le-saad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 01:11:30 by le-saad           #+#    #+#             */
/*   Updated: 2025/04/22 01:23:39 by le-saad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parsing.h"

t_redir_type token_to_redir_type(t_token_type type) { /* ... */ }
t_redir *create_redir_node(t_redir_type type, char *file_or_limiter) { /* ... */ }
void add_back_redir_node(t_redir **head, t_redir *node) { /* ... */ }
void free_redirs(t_redir *redirs) { /* ... */ }
bool has_redirections(t_token *start, t_token *end) { /* ... */ }
t_redir *get_redirs(t_token *start, t_token *end) { /* ... */ }