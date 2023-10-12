/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:33:02 by fsoares-          #+#    #+#             */
/*   Updated: 2023/10/12 17:53:02 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_HANDLER_H
# define PIPE_HANDLER_H

# include "minishell.h"

void	setup_first_read_fd(t_command *command);
void	setup_last_write_fd(t_command *command);
void	setup_pipe_read(t_command *command, int in_pipe[2]);
void	setup_pipe_write(t_command *command, int out_pipe[2]);

void	close_pipe(int pipe[2]);

#endif
