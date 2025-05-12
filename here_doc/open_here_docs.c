/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_here_docs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 02:36:51 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/11 02:38:55 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// loop over the ready_tokens linked list and over the redirs linked list
// for each here doc
// fork() and start reading from the STD_IN (0)
// pipe() and put everything in the pipe
// close the write end and save the read end in the redir here_doc_fd
// 