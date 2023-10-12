/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:20:51 by scartage          #+#    #+#             */
/*   Updated: 2023/10/12 17:37:25 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft.h"
# include "../../inc/minishell.h"

typedef struct s_builtins_fn
{
	char	*name;
	int		(*fn)(t_list *, t_list *);
}	t_builtin;

t_builtin	get_builtin(t_command *command);
int			execute_builtin(t_builtin builtin, t_command *comm, t_list *envs);

int			echo(t_list *arguments, t_list *envs);
int			pwd(t_list *arguments, t_list *envs);
int			ft_exit(t_list *arguments, t_list *envs);

#endif