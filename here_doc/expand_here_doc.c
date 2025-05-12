/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 02:34:48 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/11 02:36:46 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// read for the pip
// if the limites doesnt have quotes
// expand vars
// else skip
// pipe() again and put the ready to be treated content in it
// update the fd to the cmd fds[2]