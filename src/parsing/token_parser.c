/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:46:11 by fsoares-          #+#    #+#             */
/*   Updated: 2023/06/07 17:10:07 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "../errors/errors.h"
#include "token_parser.h"

bool	is_quote(char c);
bool	is_word_char(char c);
void	add_token(t_parse_info *info, char *token);
void	add_char_to_token(t_parse_info *info, char c);
void	process_redirection(t_parse_info *info);

t_state	handle_in_token(t_parse_info *info);

t_state	handle_in_space(t_parse_info *info)
{
	t_state	next_state;

	next_state = in_space;
	if (is_quote(info->current_char))
	{
		info->quote_char = info->current_char;
		add_char_to_token(info, info->current_char);
		next_state = in_quote;
	}
	else if (info->current_char == '|')
		add_token(info, "|");
	else if (info->current_char == '>' || info->current_char == '<')
		process_redirection(info);
	else if (is_word_char(info->current_char))
	{
		add_char_to_token(info, info->current_char);
		next_state = in_token;
	}
	else if (info->current_char == ' ')
		next_state = in_space;
	else
		shell_error("Problem parsing tokens in_space");
	return (next_state);
}

t_state	handle_in_quote(t_parse_info *info)
{
	t_state	next_state;

	next_state = in_quote;
	if (is_quote(info->current_char))
	{
		add_char_to_token(info, info->current_char);
		if (info->current_char == info->quote_char)
			next_state = in_token;
	}
	else
		add_char_to_token(info, info->current_char);
	return (next_state);
}

/*Hay que solucionar cuando el input es un espacio (32)*/
t_parse_info	new_info(char *line)
{
	t_parse_info	info;

	info.line = line;
	info.current_char = line[0];
	info.pos = 1;
	info.token = new_builder();
	if (info.token == NULL)
		abort_perror("Creating string to save tokens");
	info.tokens = NULL;
	return (info);
}

t_list	*parse_line(char *line)
{
	t_state			current_state;
	t_parse_info	info;

	info = new_info(line);
	current_state = in_space;
	while (info.current_char)
	{
		if (current_state == in_space)
			current_state = handle_in_space(&info);
		else if (current_state == in_token)
			current_state = handle_in_token(&info);
		else if (current_state == in_quote)
			current_state = handle_in_quote(&info);
		else
			shell_error("wtf, it should never do this (token parsing)");
		info.current_char = line[info.pos++];
	}
	if (current_state == in_token || current_state == in_quote)
		add_token(&info, info.token->buffer);
	free_builder(info.token);
	// TODO: Maybe free line
	return (info.tokens);
}
