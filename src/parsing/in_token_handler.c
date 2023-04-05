/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_token_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:39:16 by fsoares-          #+#    #+#             */
/*   Updated: 2023/04/05 16:55:51 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_parser.h"
#include "../errors/errors.h"

bool	is_quote(char c);
bool	is_word_char(char c);
void	add_token(t_list **result, char *token);
void	process_redirection(t_parse_info *info);

t_state	in_token_space(t_parse_info *info)
{
	add_token(&info->tokens, info->token->buffer);
	reset_builder(info->token);
	return (in_space);
}

t_state	in_token_pipe(t_parse_info *info)
{
	add_token(&info->tokens, info->token->buffer);
	add_token(&info->tokens, "|");
	reset_builder(info->token);
	return (in_space);
}

t_state	in_token_redirection(t_parse_info *info)
{
	add_token(&info->tokens, info->token->buffer);
	process_redirection(info);
	reset_builder(info->token);
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
		append_char(info->token, info->current_char);
	else if (is_quote(info->current_char))
	{
		info->quote_char = info->current_char;
		append_char(info->token, info->current_char);
		next_state = in_quote;
	}
	else
		shell_error("Problem parsing tokens in_token");
	return (next_state);
}
