/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:55:22 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/16 03:11:22 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "../include/dependencies.h"

extern void	rl_replace_line(const char *str, int clear_undo);
extern void	rl_clear_history(void);
extern int	rl_catch_signals;

void		handle_sigint(int sig);
void		setup_signals(void);
void		reset_signals_for_child(void);
void		reset_signals_for_heredoc(void);

#endif
