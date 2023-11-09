/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:40:52 by fsoares-          #+#    #+#             */
/*   Updated: 2023/11/09 19:44:47 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_replacer.h"

t_env_info	new_env_info(char *str, t_list *envs, int last_status)
{
	t_env_info	res;

	res.pos = 0;
	res.str = str;
	res.to_add = true;
	res.res = str_new();
	res.current = in_word;
	res.envs = envs;
	res.last_status = last_status;
	return (res);
}

void	special_append(t_string *res, char *env_content)
{
	bool	in_word;
	int		i;

	in_word = false;
	i = 0;
	while (env_content[i])
	{
		if (in_word == false && env_content[i] != ' ')
		{
			str_add_char(res, '"');
			in_word = true;
		}
		if (in_word == true && env_content[i] == ' ')
		{
			str_add_char(res, '"');
			in_word = false;
		}
		if (env_content[i] == '"')
			str_add_char(res, '\\');
		str_add_char(res, env_content[i]);
		i++;
	}
	if (in_word)
		str_add_char(res, '"');
}

char	*escape_double_quote(char *orig)
{
	t_string	*res;

	res = str_new();
	while (*orig)
	{
		if (*orig == '"')
			str_add_char(res, '\\');
		str_add_char(res, *orig);
		orig++;
	}
	return (str_to_chars(res));
}
