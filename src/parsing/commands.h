/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:19:09 by scartage          #+#    #+#             */
/*   Updated: 2023/11/09 17:49:59 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "libft.h"
# include "minishell.h"

bool	valid_token_seq(t_list *tokens);
void	free_command(t_command *command);
void	free_token(void *token);
t_list	*token_to_command(t_list *tokens);
#endif
