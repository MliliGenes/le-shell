/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:55:22 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/16 01:49:46 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "../include/dependencies.h"
// # include "/goinfre/sel-mlil/homebrew/opt/readline/include/readline/history.h"

void	handle_sigint(int sig);
void	setup_signals(void);
void	reset_signals_for_child(void);
void	reset_signals_for_heredoc(void);

#endif
