/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_token_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:39:16 by fsoares-          #+#    #+#             */
/*   Updated: 2023/10/11 19:13:44 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_parser.h"
#include "../errors/errors.h"

bool	is_quote(char c);
bool	is_word_char(char c);
void	add_token(t_parse_info *info, char *token);
void	add_char_to_token(t_parse_info *info, char c);

void	process_redirection(t_parse_info *info)
{
	if (info->current_char == '>')
	{
		if (info->line[info->pos] == '>')
		{
			add_token(info, ">>");
			info->pos++;
		}
		else
			add_token(info, ">");
	}
	else if (info->current_char == '<')
	{
		if (info->line[info->pos] == '<')
		{
			add_token(info, "<<");
			info->pos++;
		}
		else
			add_token(info, "<");
	}
}

t_state	in_token_space(t_parse_info *info)
{
	add_token(info, info->token->buffer);
	str_clear(info->token);
	return (in_space);
}

t_state	in_token_pipe(t_parse_info *info)
{
	add_token(info, info->token->buffer);
	add_token(info, "|");
	str_clear(info->token);
	return (in_space);
}

t_state	in_token_redirection(t_parse_info *info)
{
	add_token(info, info->token->buffer);
	process_redirection(info);
	str_clear(info->token);
	return (in_space);
}

t_state	handle_in_token(t_parse_info *info)
{
	t_state	next_state;

	next_state = in_token;
	if (info->current_char == ' ')
		next_state = in_token_space(info);
	else if (info->current_char == '|')
		next_state = in_token_pipe(info);
	else if (info->current_char == '>' || info->current_char == '<')
		next_state = in_token_redirection(info);
	else if (is_word_char(info->current_char))
		add_char_to_token(info, info->current_char);
	else if (is_quote(info->current_char))
	{
		info->quote_char = info->current_char;
		add_char_to_token(info, info->current_char);
		next_state = in_quote;
	}
	else
		shell_error("Problem parsing tokens in_token");
	return (next_state);
}
