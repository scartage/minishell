/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:19:09 by scartage          #+#    #+#             */
/*   Updated: 2023/11/04 19:22:43 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "libft.h"
# include "minishell.h"

bool	valid_token_seq(t_list *tokens);
t_list	*token_to_command(t_list * tokens);
void	free_command(t_command *command);

#endif
