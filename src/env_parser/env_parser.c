/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:16:17 by scartage          #+#    #+#             */
/*   Updated: 2023/04/05 19:38:20 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>		//para malloc
#include "env_parser.h"

char	*get_content(char *s, int equal)
{
	return ft_substr(s, equal + 1, ft_strlen(s));
}

char	 *get_name(char *s, int equal)
{
	 return ft_substr(s, 0, equal);
}

t_list *env_parser(char **env)
{
	int i = 0;
	int first_equal = 0;
	char *equal_ptr;
	t_env_var	*envs;
	t_list		*result;

	result = NULL;
	envs = malloc(sizeof(t_env_var));
	while (env[i] != NULL)
	{
		equal_ptr = ft_strchr(env[i] , '=');
		first_equal = equal_ptr - env[i];
		envs->name = get_name(env[i], first_equal);
		envs->content = get_content(env[i], first_equal);
		ft_lstadd_back(&result, ft_lstnew(envs));
		i++;
	}
	return (result);

}
