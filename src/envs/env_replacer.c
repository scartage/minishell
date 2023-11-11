/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replacer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:54:56 by scartage          #+#    #+#             */
/*   Updated: 2023/11/11 16:29:42 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_replacer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

t_env_info	new_env_info(char *str, t_list *envs, int last_status);
void		special_append(t_string *res, char *env_content);
char		*escape_double_quote(char *orig);

int	handle_empty_dollar(t_env_info *info, char *base)
{
	int	size;

	size = 0;
	if (base[0] == '?')
	{
		str_add_int(info->res, info->last_status);
		size++;
	}
	else if (!(info->current != in_double_quote
			&& (base[0] == '"' || base[0] == '\'')))
		str_add_char(info->res, '$');
	return (size);
}

int	handle_dollar(t_env_info *info)
{
	int		size;
	char	*base;
	char	*temp;
	char	*content;

	base = info->str + info->pos + 1;
	size = 0;
	while (base[size] && ft_isalpha(base[size]))
		size++;
	if (size == 0)
		return (handle_empty_dollar(info, base));
	temp = ft_substr(base, 0, size);
	content = get_content(temp, info->envs);
	free(temp);
	if (content != NULL)
	{
		if (info->current == in_double_quote)
			str_append(info->res, escape_double_quote(content));
		else
			special_append(info->res, content);
	}
	return (size);
}

bool	should_handle_tilde(char *str, int pos)
{
	bool	should_handle;

	should_handle = str[pos] == '~' && ft_strchr(" /", str[pos + 1]);
	if (pos != 0 && str[pos - 1] != ' ')
		should_handle = false;
	return (should_handle);
}

t_state	not_single_quote_handler(t_env_info *info)
{
	int		offset;
	char	c;

	c = info->str[info->pos];
	if (info->current == in_word && c == '\'')
		return (in_single_quote);
	if (info->current == in_word && c == '"')
		return (in_double_quote);
	if (info->current == in_double_quote && c == '"')
		return (in_word);
	if (should_handle_tilde(info->str, info->pos))
	{
		str_append(info->res, get_content("HOME", info->envs));
		info->to_add = false;
	}
	if (c == '$')
	{
		offset = handle_dollar(info);
		info->pos += offset;
		info->to_add = false;
	}
	return (info->current);
}

char	*replace_envs(char *str, t_list *envs, int last_status)
{
	t_env_info	info;

	info = new_env_info(str, envs, last_status);
	while (str[info.pos])
	{
		if (info.current == in_single_quote && str[info.pos] == '\'')
			info.current = in_word;
		else if (info.current != in_single_quote)
			info.current = not_single_quote_handler(&info);
		if (info.to_add)
			str_add_char(info.res, str[info.pos]);
		info.to_add = true;
		info.pos++;
	}
	free(str);
	return (str_to_chars(info.res));
}
