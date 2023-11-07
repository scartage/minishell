/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:46:08 by scartage          #+#    #+#             */
/*   Updated: 2023/11/07 19:46:25 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	add_new_end_var(char *env_name, char *value, t_list **envs)
{
	t_env_var	*new_env_var;

	new_env_var = malloc(sizeof(t_env_var));
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
	t_list		*temp;
	t_env_var	*env_var;

	temp = envs;
	while (temp != NULL)
	{
		env_var = (t_env_var *)temp->content;
		if (ft_strncmp(env_name, env_var->name, ft_strlen(env_name)) == 0)
		{
			if (env_var->content != NULL && ft_strlen(env_var->content) >= 0)
				return (2);
			return (1);
		}
		if (temp->next == NULL)
			break ;
		temp = temp->next;
	}
	return (0);
}

static int	is_valid_char_name(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || (c == '_'))
		return (0);
	return (1);
}

int	check_env_name(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (-1);
	while (arg[i] && arg[i] != '=')
	{
		if (is_valid_char_name(arg[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}
