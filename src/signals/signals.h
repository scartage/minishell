/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:52:23 by scartage          #+#    #+#             */
/*   Updated: 2023/11/04 18:52:24 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	signals(int i);
void	set_signal_handler(void (*handler)(int));
void	signal_handler_input(int signal);
void	signal_handler_executing(int signal);

#endif
