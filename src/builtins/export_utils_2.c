/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:46:08 by scartage          #+#    #+#             */
/*   Updated: 2023/10/19 19:28:59 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*aqui debo meter mas funciones relacionaddas al export*/

void	add_new_end_var(char *env_name, char *value, t_list **envs)
{
	t_env_var *new_env_var = malloc(sizeof(t_env_var));
	if (new_env_var == NULL)
	{
		perror("failed to allocate memory in add_env_var");
		exit(EXIT_FAILURE);
	}
	new_env_var->name = ft_strdup(env_name);
	if (value == NULL)
		new_env_var->content = NULL;
	else
		new_env_var->content = ft_strdup(value);
	ft_lstadd_back(envs, ft_lstnew(new_env_var));
}

int	var_exists_in_envs(char *env_name, t_list *envs)
{
	t_list *temp = envs;

	while (temp != NULL)
	{
		t_env_var *env_var = (t_env_var *)temp->content;
		if (ft_strncmp(env_name, env_var->name, ft_strlen(env_name)) == 0)
		{
			if (env_var->content != NULL && ft_strlen(env_var->content) >= 0)
				return (2);
			return (1);
		}
		if (temp->next == NULL)
			break;
		temp = temp->next;
	}
	return (0);
}

int	check_env_name(char *arg)
{
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
	{
		return (-1);
	}
	return (0);
}

static void	swap_nodes(t_list *node1, t_list *node2)
{
	t_env_var *temp_env_var = (t_env_var *)node1->content;
	node1->content = node2->content;
	node2->content = temp_env_var;
}

void	order_envs_list(t_list *envs)
{
	t_list *actual = envs;

	while (actual != NULL)
	{
		t_list *siguiente = actual->next;
		while (siguiente != NULL)
		{
			t_env_var *env_var_actual = (t_env_var *)actual->content;
			t_env_var *env_var_sig = (t_env_var *)siguiente->content;

			if (ft_strncmp(env_var_actual->name, env_var_sig->name, ft_strlen(env_var_actual->name)) > 0)
				swap_nodes(actual, siguiente);
			siguiente = siguiente->next;
		}
		actual = actual->next;
	}
}
