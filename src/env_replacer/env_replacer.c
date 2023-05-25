/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replacer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:54:56 by scartage          #+#    #+#             */
/*   Updated: 2023/05/25 19:53:32 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_replacer.h"
#include <stdio.h>

/*Funcion con la que comprobamos si el contenido de la
lista es correcto, dentro esta el nombre y el contenido de evnp*/
void print_content_list(t_list *env_variables)
{
	t_list* current = env_variables;
	while (current != NULL)
	{
		t_env_var* env = (t_env_var *)current->content;
		printf("name=%s\n", env->name);
		printf("content=%s\n", env->content);
		current = current->next;
	}	
}

char *replacing_envars(char *input, t_list *env_variables)
{
    printf("el input que entra:[%s]\n", input);
    //print_content_list(env_variables);
    //devolveriamos el input con las variables cambiadas
    return (input);
}