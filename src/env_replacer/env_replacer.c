/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replacer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:54:56 by scartage          #+#    #+#             */
/*   Updated: 2023/06/07 17:25:40 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_replacer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *get_content(char *env_name, t_list *env_variables)
{
	t_list *tmp = env_variables;

	while (tmp->content)
	{
		t_env_var* env = (t_env_var *)tmp->content;
		if (strcmp(env_name, env->name) == 0)
		{
			printf("encontramos coincidencia, return %s\n", env->content);
			return (env->content);
		}
		printf("no strcmp\n");
		if (tmp->next == NULL)
			break;
		tmp = tmp->next;
	}
	return (NULL);
}

typedef enum e_state
{
	in_single_quote,
	in_double_quote,
	in_env_var_name,
	in_word
}	t_state;

/*Tenemos que solucionar cuando el contenido es (NULL)*/
char *get_env_value(char *str, t_list *env_variables) {


	printf("get var: %s\n", str);
	char *res = get_content(str, env_variables);
	printf("El contenido de la env_var es: %s\n", res);
	if (res == NULL)
		return "123";
	return res;
}

char *env_replacer(char *str, t_list *env_variables) {
	int i = 0;

	t_state current = in_word;

	t_string *res = new_builder();
	t_string *env_name = new_builder();

	while (str[i])
	{
		//printf("char: %c -> status: %i\n", str[i], current);
		if (current == in_word && str[i] == '\'') {
			current = in_single_quote;
		} else if (current == in_word && str[i] == '"') {
			current = in_double_quote;
		} else if (current == in_double_quote && str[i] == '"') {
			current = in_word;
		} else if (current == in_double_quote && str[i] == '$') {
			current = in_env_var_name;
		} else if (current == in_word && str[i] == '$') {
			current = in_env_var_name;
		} else if (current == in_env_var_name && !(ft_isalnum(str[i]) || str[i] == '_')) {
			append_string(res, get_env_value(env_name->buffer, env_variables));
			printf("appen char: %c\n", str[i]);
			if (str[i] != '"')
				append_char(res, str[i]);
			reset_builder(env_name);
			current = in_word;
		} else if (current == in_single_quote && str[i] == '\'') {
			current = in_word;
		} else if (current == in_word || current == in_single_quote || current == in_double_quote) {
			append_char(res, str[i]);
		} else if  (current == in_env_var_name) {
			append_char(env_name, str[i]);
		}

		if (str[i])
			i++;
	}
	if (current == in_env_var_name) {
		append_string(res, get_env_value(env_name->buffer, env_variables));
	}
	printf("res de res: [%s]\n", res->buffer);
	free_builder(env_name);
	char *result = ft_strdup(res->buffer); // needs free
	free_builder(res);

	return result;
}

t_list *replacing_envars(t_list *input, t_list *env_variables)
{
	t_list *new_tokens = input;

	while (new_tokens->content)
	{
		env_replacer(new_tokens->content, env_variables);
		if (new_tokens->next == NULL)
			break ;
		new_tokens = new_tokens->next;
	}
    //devolveriamos el input con las variables cambiadas
    return ((t_list *)new_tokens);
}
