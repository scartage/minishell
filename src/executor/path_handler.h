/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handler.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 17:25:00 by fsoares-          #+#    #+#             */
/*   Updated: 2023/09/21 19:42:50 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_HANDLER_H
# define PATH_HANDLER_H

# include "../inc/minishell.h"

char	*get_full_path(t_command *cmd, t_list *envs);

#endif