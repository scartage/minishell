/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:40:45 by scartage          #+#    #+#             */
/*   Updated: 2023/11/03 22:09:10 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <limits.h>

bool	echo_is_valid_option(char *argument)
{
	int	len;
	int	i;

	i = 1;
	len = ft_strlen(argument);
	if (argument[0] != '-')
		return (false);
	while (i < len)
	{
		if (argument[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

/*revisada y testeada, se comporta como bash*/
int	ft_pwd(void)
{
	char	buffer[PATH_MAX];

	getcwd(buffer, PATH_MAX);
	ft_printf("%s\n", buffer);
	return (0);
}

/*these are util fn for the unset builtin*/
static void	swap_nodes(t_list *node1, t_list *node2)
{
	t_env_var	*temp_env_var;

	temp_env_var = (t_env_var *)node1->content;
	node1->content = node2->content;
	node2->content = temp_env_var;
}

void	order_envs_list(t_list *envs)
{
	t_list		*actual;
	t_list		*siguiente;
	t_env_var	*env_var_actual;
	t_env_var	*env_var_sig;

	actual = envs;
	while (actual != NULL)
	{
		siguiente = actual->next;
		while (siguiente != NULL)
		{
			env_var_actual = (t_env_var *)actual->content;
			env_var_sig = (t_env_var *)siguiente->content;
			if (ft_strncmp(env_var_actual->name, env_var_sig->name,
					ft_strlen(env_var_actual->name)) > 0)
				swap_nodes(actual, siguiente);
			siguiente = siguiente->next;
		}
		actual = actual->next;
	}
}