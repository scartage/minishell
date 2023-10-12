/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:49:16 by fsoares-          #+#    #+#             */
/*   Updated: 2023/10/12 17:40:17 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_HANDLER_H
# define FILE_HANDLER_H

# include "minishell.h"

int	open_read_perm(char *path);

int	open_write_perm(char *path, bool is_heredoc);

int	get_input_fd(t_list *in_files);

int	get_output_fd(t_list *out_files);

#endif