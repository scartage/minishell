/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:32:34 by fsoares-          #+#    #+#             */
/*   Updated: 2023/11/09 17:48:46 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_PARSER_H
# define TOKEN_PARSER_H

# include "libft.h"

typedef enum e_state
{
	in_space,
	in_token,
	in_quote,
}	t_state;

typedef struct s_parse_info {
	char		current_char;
	char		*line;
	t_string	*token;
	int			pos;
	char		quote_char;
	t_list		*tokens;
}	t_parse_info;

// Public method
t_list	*parse_line(char *line);

#endif