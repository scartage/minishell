/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replacer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:54:56 by scartage          #+#    #+#             */
/*   Updated: 2023/10/13 16:24:33 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_replacer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern t_gShell g_shell;

char *get_content(char *env_name, t_list *env_variables)
{
	t_list *tmp = env_variables;

	while (tmp != NULL)
	{
		t_env_var* env = (t_env_var *)tmp->content;
		if (ft_strncmp(env_name, env->name, ft_strlen(env_name)) == 0)
		{
			return (env->content);
		}
		if (tmp->next == NULL)
			break;
		tmp = tmp->next;
	}
	return ("");
}

typedef enum e_state
{
	in_single_quote,
	in_double_quote,
	in_env_var_name,
	in_word
}	t_state;

/*Tenemos que solucionar cuando el contenido es (NULL)
	en la lista de tokens que obtenemos, si el valor de la variable de entorno esta vacio
	nos dejara un espacio en blanco en el array, esto puede traer problemas a futuro*/
char *get_env_value(char *str, t_list *env_variables) {

	char *res = get_content(str, env_variables);
	return res;
}

char *env_replacer(char *str, t_list *env_variables) {
	int i = 0;

	t_state current = in_word;

	t_string *res = str_new();
	t_string *env_name = str_new();

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
		} else if (current == in_env_var_name && !(ft_isalnum(str[i])))
		{
			if (str[i] == '$')
 			{
    	    	str_append(res, get_env_value(env_name->buffer, env_variables));
    	   		current = in_env_var_name;
			}
			else if (str[i] == '?' && str[i-1] == '$')
			{
				str_add_int(res, g_shell.last_execution);
				current = in_word;
			}
			else
			{
 				str_append(res, get_env_value(env_name->buffer, env_variables));
				if (str[i] != '"')
					str_add_char(res, str[i]);
				current = in_word;			
			}
			str_clear(env_name);
		} else if (current == in_single_quote && str[i] == '\'') {
			current = in_word;
		} else if (current == in_word || current == in_single_quote || current == in_double_quote) {
			str_add_char(res, str[i]);
		} else if  (current == in_env_var_name) {
			str_add_char(env_name, str[i]);
		}
		if (str[i])
			i++;
	}
	if (current == in_env_var_name) {
		str_append(res, get_env_value(env_name->buffer, env_variables));
		current = in_word;
	}
	str_free(env_name);
	char *result = ft_strdup(res->buffer); // needs free
	str_free(res);

	return result;
}

t_list *replacing_envars(t_list *input, t_list *env_variables)
{
	t_list *new_tokens = input;
	t_list *current_tokens = new_tokens;

	while (current_tokens != NULL)
	{
		current_tokens->content = env_replacer(current_tokens->content, env_variables);
		if (current_tokens->next == NULL)
			break ;
		current_tokens = current_tokens->next;
	}
    return (new_tokens);
}
