/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:43:14 by fsoares-          #+#    #+#             */
/*   Updated: 2023/04/05 16:45:59 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_parser.h"

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

void	process_redirection(t_parse_info *info)
{
	if (info->current_char == '>')
	{
		if (info->line[info->pos] == '>')
		{
			add_token(&info->tokens, ">>");
			info->pos++;
		}
		else
			add_token(&info->tokens, ">");
	}
	else if (info->current_char == '<')
	{
		if (info->line[info->pos] == '<')
		{
			add_token(&info->tokens, "<<");
			info->pos++;
		}
		else
			add_token(&info->tokens, "<");
	}
}
