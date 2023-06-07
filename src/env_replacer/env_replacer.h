/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replacer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:55:59 by scartage          #+#    #+#             */
/*   Updated: 2023/06/07 16:36:00 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_REPLACER_H
# define ENV_REPLACER_H

# include "libft.h"
# include "../env_parser/env_parser.h"
# include <stdio.h>


t_list* replacing_envars(t_list *input, t_list *env_variables);

/*Utils*/
void print_content_list(t_list *env_variables);
bool can_change(char *s, int *n_envs);
bool has_env_char(char *s, int *n_envs);
bool check_quotes(char *s);
bool is_uppercase(char *s);
bool is_space(char *s);
#endif