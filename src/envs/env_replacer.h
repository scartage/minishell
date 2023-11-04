/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replacer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:55:59 by scartage          #+#    #+#             */
/*   Updated: 2023/11/04 17:07:51 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_REPLACER_H
# define ENV_REPLACER_H

# include "libft.h"
# include "minishell.h"
# include "env_parser.h"
# include <stdio.h>

t_list	*remove_quotes(t_list *input);
char *replace_envs(char *str, t_list *envs, int last_status);

#endif