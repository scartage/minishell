/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:41:31 by scartage          #+#    #+#             */
/*   Updated: 2023/10/25 18:51:29 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	update_env_content(char *env_name, char *value, t_list *envs)
{
	t_list		*temp;
	t_env_var	*env_var;

	temp = envs;
	while (temp != NULL)
	{
		env_var = (t_env_var *)temp->content;
		if (ft_strncmp(env_name, env_var->name, ft_strlen(env_name)) == 0)
		{
			free(env_var->content);
			env_var->content = ft_strdup(value);
			break ;
		}
		if (temp->next == NULL)
			break ;
		temp = temp->next;
	}
}

static void	set_env_value_to_null(char *env_name, t_list *envs)
{
	t_list *temp = envs;
	int found = 0;
	while (temp != NULL)
	{
		t_env_var *env_var = (t_env_var *)temp->content;
		if (ft_strncmp(env_name, env_var->name, ft_strlen(env_name)) == 0)
		{
			free(env_var->content); // liberamos memoria del valor anterior
			env_var->content = ft_strdup("");
			found = 1;
			break ;
		}
		temp = temp->next;
	}
	if (found != 1)
		add_new_end_var(env_name, "", &envs);
}

static int	check_spaces_bt_equal(char *arg)
{
	char *equal = ft_strchr(arg, '=');

	int index_equal = 0;

	if (equal == NULL)
		return (0);
	index_equal = equal - arg;
	if (arg[index_equal - 1] == ' ')
	{
		if (arg[index_equal + 1] == ' '
			|| (arg[index_equal + 1] != ' ' && arg[index_equal + 1] != '\0'))
		{
			return (1);
		}
	}
	return (0);
}


static void	env_var_with_value(char *arg, t_list *envs)
{
	char *equal = ft_strchr(arg, '=');

	if (equal)
	{
		char *name = ft_substr(arg, 0, equal - arg);
		char *value = ft_substr(arg, (equal + 1) - arg, ft_strlen(arg));
		if (ft_strlen(value) == 0)
		{
			set_env_value_to_null(name, envs);
		}
		else
		{
			if (var_exists_in_envs(name, envs) != 0)
				update_env_content(name, value, envs);
			else
				add_new_end_var(name, value, &envs);
		}
	}
}

int	check_env_arg(char *arg, t_list *envs)
{
	int flag = 0;
	if (check_env_name(arg) != 0)
		return (1);
	if (check_spaces_bt_equal(arg) != 0)
		return (1);
	if (arg[ft_strlen(arg) - 1] == '=')
	{
		char *parse_arg = ft_substr(arg, 0, ft_strlen(arg) - 1);
		set_env_value_to_null(parse_arg, envs);
		free(parse_arg);
	}
	char *is_equal_insdide = ft_strchr(arg, '=');
	if (is_equal_insdide != NULL)
		flag = 1;
	//si dentro de arg no hay un = y tampoco esta en envs, la creo con value NULL
	else if (flag == 0 && var_exists_in_envs(arg, envs) == 0)
		add_new_end_var(arg, NULL, &envs);
	if (flag == 1)
		env_var_with_value(arg, envs);
	return (0);
}