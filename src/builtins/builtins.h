/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:20:51 by scartage          #+#    #+#             */
/*   Updated: 2023/10/13 18:56:43 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft.h"
# include "minishell.h"

typedef struct s_builtins_fn
{
	char	*name;
	int		(*fn)(t_list *, t_list *);
}	t_builtin;

t_builtin	get_builtin(t_command *command);

int 		echo(t_list *arguments, t_list *envs);
int 		pwd(t_list *arguments, t_list *envs);
int 		ft_exit(t_list *arguments, t_list *envs);
int 		ft_cd(t_list *arguments, t_list *envs);
int 		ft_env(t_list *arguments, t_list *envs);
#endif