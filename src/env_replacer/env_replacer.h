/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replacer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyb3rn4ut4 <cyb3rn4ut4@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:55:59 by scartage          #+#    #+#             */
/*   Updated: 2023/05/30 23:45:45 by cyb3rn4ut4       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_REPLACER_H
# define ENV_REPLACER_H

# include "libft.h"
# include "../env_parser/env_parser.h"

typedef struct s_env_var {
	char	*name;
	char	*content;
}	t_env_var;

t_list* replacing_envars(t_list *input, t_list *env_variables);

/*Utils*/
void print_content_list(t_list *env_variables);
bool can_change(char *s, int *n_envs);
bool has_env_char(char *s, int *n_envs);
bool check_quotes(char *s);
#endif