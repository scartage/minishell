/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:46:11 by fsoares-          #+#    #+#             */
/*   Updated: 2023/04/04 20:30:01 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_parser.h"
#include "libft.h"
#include <stdio.h>

bool	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

bool	is_word_char(char c)
{
	if (c == ' ' || is_quote(c))
		return (false);
	else
		return (true);
}

void	add_token(t_list **result, char *token)
{
	ft_lstadd_back(result, ft_lstnew(ft_strdup(token)));
}

t_list	*parse_line(char *line)
{
	t_state		current_state;
	t_list		*result;
	char		current_char;
	t_string	*word;
	char		open_quote;

	word = new_builder();
	current_state = in_space;
	current_char = *line++;
	result = NULL;
	while (current_char)
	{
		//printf("state: %i, char: %c\n", current_state, current_char);
		if (current_state == in_space && is_quote(current_char))
		{
			open_quote = current_char;
			append_char(word, current_char);
			current_state = in_quote;
		}
		else if (current_state == in_space && current_char == '|')
		{
			add_token(&result, "|");
		}
		else if (current_state == in_space && current_char == '>')
		{
			if (*line == '>') {
				add_token(&result, ">>");
				line++;
			} else {
				add_token(&result, ">");
			}
		}
		else if (current_state == in_space && current_char == '<')
		{
			if (*line == '<') {
				add_token(&result, "<<");
				line++;
			} else {
				add_token(&result, "<");
			}
		}
		else if (current_state == in_space && is_word_char(current_char))
		{
			append_char(word, current_char);
			current_state = in_word;
		}
		
		// in word
		else if (current_state == in_word && current_char == ' ')
		{
			current_state = in_space;
			add_token(&result, word->buffer);
			word = new_builder();
		}
		else if (current_state == in_word && current_char == '|')
		{
			current_state = in_space;
			add_token(&result, word->buffer);
			add_token(&result, "|");
			word = new_builder();
		}
		else if (current_state == in_word && current_char == '>')
		{
			current_state = in_space;
			add_token(&result, word->buffer);
			if (*line == '>') {
				add_token(&result, ">>");
				line++;
			} else {
				add_token(&result, ">");
			}
			word = new_builder();
		}
		else if (current_state == in_word && current_char == '<')
		{
			current_state = in_space;
			add_token(&result, word->buffer);
			if (*line == '<') {
				add_token(&result, "<<");
				line++;
			} else {
				add_token(&result, "<");
			}
			word = new_builder();
		}
		else if (current_state == in_word && is_word_char(current_char))
		{
			append_char(word, current_char);
		}
		else if (current_state == in_word && is_quote(current_char))
		{
			open_quote = current_char;
			append_char(word, current_char);
			current_state = in_quote;
		}
		
		// in quote
		else if (current_state == in_quote && is_quote(current_char))
		{
			append_char(word, current_char);
			if (current_char == open_quote)
				current_state = in_word;
		}
		else if (current_state == in_quote && !is_quote(current_char))
		{
			append_char(word, current_char);
		}

		current_char = *line++;
	}
	if (current_state == in_word || current_state == in_quote) {
		//printf("word: >%s<\n", word->buffer);
		add_token(&result, word->buffer);
	}
	return (result);
}
