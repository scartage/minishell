/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replacer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:54:56 by scartage          #+#    #+#             */
/*   Updated: 2023/11/07 20:44:08 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_replacer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *get_content(char *env_name, t_list *env_variables)
{
	t_list *tmp = env_variables;

	while (tmp != NULL)
	{
		t_env_var* env = (t_env_var *)tmp->content;
		if (ft_strncmp(env_name, env->name, ft_strlen(env_name) + 1) == 0)
		{
			return (env->content);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

typedef enum e_state
{
	in_single_quote,
	in_double_quote,
	in_env_var_name,
	in_word,
	in_space
}	t_state;

t_token *del_quotes(t_token *token) {
	int i = 0;

	t_state current = in_word;

	t_string *res = str_new();
	char *str = token->value;

	while (str[i])
	{
		//printf("char: %c -> status: %i\n", str[i], current);
		if (current == in_word && str[i] == '\'') {
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
	char *result = ft_strdup(res->buffer);
	str_free(res);
	free(str);
	token->value = result;
	return token;
}

t_list *remove_quotes(t_list *input)
{
	t_list *new_tokens = input;
	t_list *current_tokens = new_tokens;

	while (current_tokens != NULL)
	{
		current_tokens->content = del_quotes(current_tokens->content);
		if (current_tokens->next == NULL)
			break ;
		current_tokens = current_tokens->next;
	}
    return (new_tokens);
}

void special_append(t_string *res, char *env_content)
{
	bool in_word = false;
	int i = 0;
	
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

char *escape_double_quote(char *orig)
{
	t_string *res = str_new();
	
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
	int size = 0;
	char *temp;
	
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
	char *content = get_content(temp, envs);
	if (content != NULL)
	{
		if (state == in_double_quote)
			str_append(res, escape_double_quote(content));
		else
			special_append(res, content);
	}
	return (size);
}

bool should_handle_tilde(char *str, int pos) {
	bool should_handle;
	
	should_handle = str[pos] == '~' && ft_strchr(" /", str[pos + 1]);
	if (pos != 0 && str[pos - 1] != ' ')
		should_handle = false;
	return (should_handle);
}

char *replace_envs(char *str, t_list *envs, int last_status)
{
	t_state current = in_word;
	t_string *res = str_new();
	bool to_add = true;
	
	int i = 0;
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
			int offset = handle_dollar(res, str + i + 1, current, last_status, envs);
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
