/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:49:16 by fsoares-          #+#    #+#             */
/*   Updated: 2023/09/21 19:43:32 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_HANDLER_H
# define FILE_HANDLER_H

#include "../inc/minishell.h"

int		open_read_perm(char *path);

int		open_write_perm(char *path, bool is_heredoc);

void	setup_pipes(t_command *comm, int in_pipe[2], int out_pipe[2]);

void	close_pipe(int pipe[2]);

#endif