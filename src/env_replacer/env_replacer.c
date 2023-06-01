/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replacer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:54:56 by scartage          #+#    #+#             */
/*   Updated: 2023/06/01 20:05:17 by scartage         ###   ########.fr       */
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
		if (strcmp(env_name, env->name))
			return (env->content);
		if (tmp->next == NULL)
			break;
		tmp = tmp->next;
	}
	return (NULL);
}

/*char* get_substring(const char* string, char start, char end)
{
    const char* start_ptr;
    const char* end_ptr;

    start_ptr = strchr(string, start);
	printf("start_ptr -> %c\n", *start_ptr);
 	end_ptr = strchr(string, end);
	printf("end_ptr -> %c\n", *end_ptr);
   

	printf("start_ptr: [%c], end_ptr: [%c], len: [%d]\n", *start_ptr, *end_ptr, end_ptr < start_ptr);
    if (start_ptr == NULL || end_ptr == NULL || end_ptr < start_ptr) {
		printf("se fue por aqui\n");
        return NULL;  // No se encontró el inicio o el final, o están en el orden incorrecto
    }
    size_t length = end_ptr - start_ptr - 1;
    char* substring = malloc(length + 1);
	if (substring == NULL)
		return (NULL);
    ft_strlcpy(substring, start_ptr + 1, length);
    substring[length] = '\0';
	printf("subs: [%s]\n", substring);
    tengo que revisar que valor es susbtring y probar esto
	if (substring == '\0')
		get_substring(str, '$', '$');
   // return substring;
   return (substring);
}*/

char* get_substring(const char* string, char start)
{
    const char* start_ptr = strchr(string, start);
    if (start_ptr == NULL) {
        return NULL;  // No se encontró el carácter de inicio
    }
    
    const char* end_ptr = strpbrk(start_ptr + 1, " $");
    if (end_ptr == NULL) {
        end_ptr = strchr(start_ptr, '\0');  // Si no se encuentra un espacio ni un '$', se toma el fin de cadena
    }
    
    size_t length = end_ptr - start_ptr - 1;
    char* substring = malloc(length + 1);
    if (substring == NULL) {
        return NULL;  // Error de asignación de memoria
    }
    
    strncpy(substring, start_ptr + 1, length);
    substring[length] = '\0';
	if (is_uppercase(substring))
    	return substring;
	return (NULL);
}

/*La idea es ir revisando los tokens validos e ir cambiando las variables de entorno dentro de estos
para cambiar por el valor de la env var necesitamos saber su nombre, la funcion de arriba hace eso, pero tengo que mejorar el saber
cuales tokens entran como validos y cuales no.

ademas, ver otros casos donde NO puedo sacar el env_var como -> $teste (este solo, sin quoutes ni nada no funciona en la func de arriba)*/
char *change_env(char *str, int *n_envs, t_list *env_variables)
{
	(void)env_variables;
	char *new_str = NULL;		//string a devolver al contenido (ya env cambiado)
	char *tmp_s = NULL;			
	char *env_name;				//nombre de env_var
	int i = *n_envs;


	while (i > 0)
	{
		tmp_s = get_substring(str, '$');
		env_name = tmp_s;
		printf("env_var_name: [%s]\n", tmp_s);
		if (env_name == NULL)
		{
			printf("another round\n");
			i--;
		}
		/*Una vez con el nombre, podemos buscar el contenido en env_vars*/

		//tmp_s = get_content(env_name, env_variables);
		//printf("env_var_content: [%s]\n", tmp_s);
		else
		{
			printf("n_envs: %d\n", i);
			i--;
		}
	}
	
	//printf("mas de 1 env_var se hara en un futuro\n");
	return (new_str);
}

t_list *replacing_envars_orig(t_list *input, t_list *env_variables)
{
	t_list *new_tokens = input;
	int n_envs;
	(void )*env_variables;
	
	while (new_tokens->content)
	{
		n_envs = 0;
		if (can_change(new_tokens->content, &n_envs))
		{
			printf("token a cambiar: [%s] tiene: [%d] variables de entorno\n", (char *)new_tokens->content, n_envs);
			new_tokens->content = change_env(new_tokens->content, &n_envs, env_variables);
			//printf("token cambiado: [%s]\n", new_tokens->content);
		}
		if (new_tokens->next == NULL)
			break;
		new_tokens = new_tokens->next;
	}
    //devolveriamos el input con las variables cambiadas
    return ((t_list *)new_tokens);
}

typedef enum e_state
{
	in_single_quote,
	in_double_quote,
	in_env_var_name,
	in_word
}	t_state;

char *get_env_value(char *str) {
	printf("get var: %s\n", str);
	(void)str;
	return "123";
}

char *env_replacer(char *str) {
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
			append_string(res, get_env_value(env_name->buffer));
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
		append_string(res, get_env_value(env_name->buffer));
	}

	printf("res: %s\n", res->buffer);
	free_builder(env_name);
	char *result = ft_strdup(res->buffer); // needs free
	free_builder(res);

	return result;
}

t_list *replacing_envars(t_list *input, t_list *env_variables)
{
	t_list *new_tokens = input;
	int n_envs;
	(void )*env_variables;
	(void)n_envs;
	
	while (new_tokens->content)
	{
		env_replacer(new_tokens->content);
		new_tokens = new_tokens->next;
	}
    //devolveriamos el input con las variables cambiadas
    return ((t_list *)new_tokens);
}
