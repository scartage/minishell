/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:15:16 by scartage          #+#    #+#             */
/*   Updated: 2023/11/07 19:28:39 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_PARSER_H
# define ENV_PARSER_H

# include "libft.h"

typedef struct s_env_var {
	char	*name;
	char	*content;
}	t_env_var;

t_list	*env_parser(char **env);
#endif
