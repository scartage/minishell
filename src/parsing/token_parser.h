/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:32:34 by fsoares-          #+#    #+#             */
/*   Updated: 2023/04/04 18:21:48 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_PARSER_H
# define TOKEN_PARSER_H

#include "libft.h"

typedef enum e_state
{
	in_space,
	in_word,
	in_quote,
}	t_state;

typedef enum e_events
{
	quote,
	space,
	character,
}	t_events;

t_list	*parse_line(char *line);

#endif