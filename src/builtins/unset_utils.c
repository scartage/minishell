/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:43:01 by scartage          #+#    #+#             */
/*   Updated: 2023/11/07 19:36:20 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	free_env_var(void *envVarPtr)
{
	t_env_var	*env_var;

	env_var = (t_env_var *)envVarPtr;
	free(env_var->name);
	free(env_var->content);
	free(env_var);
}

t_list	*find_env_var(const char *arg, t_list *envs)
{
	t_list		*temp;
	t_env_var	*env_var;

	temp = envs;
	while (temp != NULL)
	{
		env_var = (t_env_var *)temp->content;
		if (ft_strncmp(arg, env_var->name, ft_strlen(arg)) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

int	remove_if_valid(char *arg, t_list **envs)
{
	if (check_env_name(arg) != 0)
		return (1);
	ft_lstremove(envs, find_env_var(arg, *envs), free_env_var);
	return (0);
}
