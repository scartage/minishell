/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:46:08 by scartage          #+#    #+#             */
/*   Updated: 2023/10/18 18:11:53 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*aqui debo meter mas funciones relacionaddas al export*/

static void swap_nodes(t_list *node1, t_list *node2)
{
	t_env_var *temp_env_var = (t_env_var *)node1->content;
	node1->content = node2->content;
	node2->content = temp_env_var;
}

void order_envs_list(t_list *envs)
{
	t_list *actual = envs;

	while (actual != NULL)
	{
		t_list *siguiente = actual->next;
		while (siguiente != NULL)
		{
			t_env_var *env_var_actual = (t_env_var *)actual->content;
			t_env_var *env_var_sig = (t_env_var *)siguiente->content;

			//compara los nombre y actualiza si es necesario
			if (ft_strncmp(env_var_actual->name, env_var_sig->name, ft_strlen(env_var_actual->name)) > 0)
			{
				swap_nodes(actual, siguiente);
			}
			siguiente = siguiente->next;
		}
		actual = actual->next;
	}
}
