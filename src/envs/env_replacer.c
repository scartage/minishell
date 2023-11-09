/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replacer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:54:56 by scartage          #+#    #+#             */
/*   Updated: 2023/11/09 18:01:35 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_replacer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum e_state
{
	in_single_quote,
	in_double_quote,
	in_env_var_name,
	in_word,
	in_space
}	t_state;

char	*get_content(char *env_name, t_list *env_variables)
{
	t_list		*tmp;
	t_env_var	*env;

	tmp = env_variables;
	while (tmp != NULL)
	{
		env = (t_env_var *)tmp->content;
		if (ft_strncmp(env_name, env->name, ft_strlen(env_name) + 1) == 0)
		{
			return (env->content);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

t_token	*del_quotes(t_token *token)
{
	int			i;
	t_state		current;
	t_string	*res;
	char		*str;
	char		*result;

	i = 0;
	current = in_word;
	res = str_new();
	str = token->value;
	while (str[i])
	{
		if (current == in_word && str[i] == '\''){
			current = in_single_quote;
		} else if (current == in_word && str[i] == '"') {
			current = in_double_quote;
		} else if (current == in_double_quote && str[i] == '\\' && str[i + 1] == '"'){
			str_add_char(res, '"');
			i++;
		} else if (current == in_double_quote && str[i] == '"') {
			current = in_word;
		} else if (current == in_single_quote && str[i] == '\'') {
			current = in_word;
		} else if (current == in_word || current == in_single_quote || current == in_double_quote) {
			str_add_char(res, str[i]);
		}
		if (str[i])
			i++;
	}
	result = ft_strdup(res->buffer);
	str_free(res);
	free(str);
	token->value = result;
	return token;
}

t_list	*remove_quotes(t_list *input)
{
	t_list	*new_tokens;
	t_list	*current_tokens;

	new_tokens = input;
	current_tokens = new_tokens;
	while (current_tokens != NULL)
	{
		current_tokens->content = del_quotes(current_tokens->content);
		if (current_tokens->next == NULL)
			break ;
		current_tokens = current_tokens->next;
	}
    return (new_tokens);
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
	while (*orig) {
		if (*orig == '"')
			str_add_char(res, '\\');
		str_add_char(res, *orig);
		orig++;
	}
	return str_to_chars(res);
}

int	handle_dollar(t_string *res, char *str, t_state state, int last_status, t_list *envs)
{
	int		size;
	char	*temp;
	char	*content;

	size = 0;
	while (str[size] && ft_isalpha(str[size]))
		size++;
	if (size == 0)
	{
		if (str[0] == '?')
		{
			str_add_int(res, last_status);
			size++;
		}
		else {
			if (!(state != in_double_quote && (str[0] == '"' || str[0] == '\''))) {
				str_add_char(res, '$');
			}
		}
		return (size);
	}
	temp = ft_substr(str, 0, size);
	content = get_content(temp, envs);
	if (content != NULL)
	{
		if (state == in_double_quote)
			str_append(res, escape_double_quote(content));
		else
			special_append(res, content);
	}
	return (size);
}

bool	should_handle_tilde(char *str, int pos) {
	bool should_handle;
	
	should_handle = str[pos] == '~' && ft_strchr(" /", str[pos + 1]);
	if (pos != 0 && str[pos - 1] != ' ')
		should_handle = false;
	return (should_handle);
}

char	*replace_envs(char *str, t_list *envs, int last_status)
{
	t_state		current;
	t_string	*res;
	bool		to_add;
	int			i;
	int			offset;

	current = in_word;
	res = str_new();
	to_add = true;
	i = 0;
	while (str[i])
	{
		if (current == in_word && str[i] == '\'') {
			current = in_single_quote;
		} else if (current == in_single_quote && str[i] == '\'') {
			current = in_word;
		} else if (current == in_word && str[i] == '"') {
			current = in_double_quote;
		} else if (current == in_double_quote && str[i] == '"') {
			current = in_word;
		} else if (current != in_single_quote && should_handle_tilde(str, i)) {
			str_append(res, get_content("HOME", envs));
			to_add = false;
		} else if (current != in_single_quote && str[i] == '$') {
			offset = handle_dollar(res, str + i + 1, current, last_status, envs);
			i += offset;
			to_add = false;
		}
		if (to_add)
			str_add_char(res, str[i]);
		to_add = true;
		i++;
	}
	free(str);
	return (str_to_chars(res));
}
