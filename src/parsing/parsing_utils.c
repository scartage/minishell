/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:43:14 by fsoares-          #+#    #+#             */
/*   Updated: 2023/10/11 19:07:34 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "token_parser.h"
#include "../errors/errors.h"

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

void	free_info(t_parse_info *info)
{
	free(info->line);
	str_free(info->token);
	ft_lstclear(&info->tokens, free);
}

void	add_token(t_parse_info *info, char *token)
{
	char	*temp;
	t_list	*new;

	temp = ft_strdup(token);
	if (temp == NULL)
	{
		free_info(info);
		abort_perror("Creating token while parsing tokens");
	}
	new = ft_lstnew(temp);
	if (new == NULL)
	{
		free(temp);
		free_info(info);
		abort_perror("Creating lists while parsing tokens");
	}
	ft_lstadd_back(&info->tokens, new);
}

void	add_char_to_token(t_parse_info *info, char c)
{
	if (str_add_char(info->token, c) < 0)
	{
		free_info(info);
		abort_perror("Adding char to token while parsing");
	}
}
