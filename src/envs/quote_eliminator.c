/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_eliminator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:51:46 by fsoares-          #+#    #+#             */
/*   Updated: 2023/11/09 20:16:11 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_replacer.h"

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

int	do_other(t_state current, t_string *res, char c)
{
	if (current == in_word && c == '\'')
		current = in_single_quote;
	else if (current == in_word && c == '"')
		current = in_double_quote;
	else if (current == in_double_quote && c == '"')
		return (in_word);
	else if (current == in_single_quote && c == '\'')
		return (in_word);
	else if (current == in_word || current == in_single_quote
		|| current == in_double_quote)
		str_add_char(res, c);
	return (current);
}

void	del_quotes(t_token *token)
{
	int			i;
	t_state		current;
	t_string	*res;
	char		*result;

	i = 0;
	current = in_word;
	res = str_new();
	while (token->value[i])
	{
		if (current == in_double_quote
			&& token->value[i] == '\\' && token->value[i + 1] == '"')
		{
			str_add_char(res, '"');
			i++;
		}
		else
			current = do_other(current, res, token->value[i]);
		if (token->value[i])
			i++;
	}
	result = ft_strdup(res->buffer);
	str_free(res);
	free(token->value);
	token->value = result;
}

t_list	*remove_quotes(t_list *input)
{
	t_list	*new_tokens;
	t_list	*current_tokens;

	new_tokens = input;
	current_tokens = new_tokens;
	while (current_tokens != NULL)
	{
		del_quotes(current_tokens->content);
		if (current_tokens->next == NULL)
			break ;
		current_tokens = current_tokens->next;
	}
	return (new_tokens);
}
