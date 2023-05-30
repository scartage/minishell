/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replacer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:54:56 by scartage          #+#    #+#             */
/*   Updated: 2023/05/30 19:35:06 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_replacer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_substring(const char* string, char start, char end)
{
    const char* start_ptr = strchr(string, start);
    const char* end_ptr = strchr(string, end);
    
    if (start_ptr == NULL || end_ptr == NULL || end_ptr < start_ptr) {
        return NULL;  // No se encontró el inicio o el final, o están en el orden incorrecto
    }
    
    size_t length = end_ptr - start_ptr - 1;
    char* substring = malloc(length + 1);
	if (substring == NULL)
		return (NULL);
    strncpy(substring, start_ptr + 1, length);
    substring[length] = '\0';
    
    return substring;
}

/*La idea es ir revisando los tokens validos e ir cambiando las variables de entorno dentro de estos
para cambiar por el valor de la env var necesitamos saber su nombre, la funcion de arriba hace eso, pero tengo que mejorar el saber
cuales tokens entran como validos y cuales no.

ademas, ver otros casos donde NO puedo sacar el env_var como -> $teste (este solo, sin quoutes ni nada no funciona en la func de arriba)*/
char *change_env(char *str, int *n_envs, t_list *env_variables)
{
	(void)*env_variables;
	printf("hay tantos envs: [%d]\n", *n_envs);
	char *new_str = NULL;		//string a devolver al contenido (ya env cambiado)
	char *tmp_s = NULL;			
	char *env_name;				//nombre de env_var

	if (*n_envs == 1)
	{
		tmp_s = get_substring(str, '$', ' ');
		env_name = tmp_s;
		printf("env_var_name: [%s]\n", env_name);
	}
	else
		printf("mas de 1 env_var se hara en un futuro\n");
	return (new_str);
}

t_list *replacing_envars(t_list *input, t_list *env_variables)
{
	t_list *new_tokens = input;
	int n_envs;
	(void )*env_variables;
	
	while (new_tokens->content)
	{
		n_envs = 0;
		if (can_change(new_tokens->content, &n_envs))
		{
			printf("token a cambiar: [%s] tiene: [%d] variables de entorno\n", new_tokens->content, n_envs);
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