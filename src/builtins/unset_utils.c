/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:43:01 by scartage          #+#    #+#             */
/*   Updated: 2023/10/18 19:39:26 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "builtins.h"

static void free_env_var(void *envVarPtr) {
    printf("limpiando nodo\n");
    t_env_var *env_var = (t_env_var *)envVarPtr;
    free(env_var->name);
    free(env_var->content);
    free(env_var);
}

t_list *find_env_var(const char *arg, t_list *envs)
{
    t_list *temp = envs;

    while (temp != NULL)
    {
        t_env_var *env_var = (t_env_var *)temp->content;
        if (ft_strncmp(arg, env_var->name, ft_strlen(arg)) == 0)
        {
            printf("si hay env_var para borrar\n");
            return (temp);  //devuelve el nodo, si coincide nombre
        }
        temp = temp->next;
    }
    printf("no hay esa env_var: %s\n", arg);
    return (NULL);  //la variable de entorno no se encontro
}

static int check_env_name(char *arg)
{
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
	{
		return (-1);
	}
	return (0);
}

int check_if_valid(char *arg, t_list **envs)
{
    if (check_env_name(arg) != 0)
		return (1);
    printf("el nombre es correcto\n");
    ft_lstremove(envs, find_env_var(arg, *envs), free_env_var);
    return (0);
}



