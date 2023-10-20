/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:20:51 by scartage          #+#    #+#             */
/*   Updated: 2023/10/20 19:00:22 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft.h"
# include "minishell.h"
# include "../envs/env_parser.h"
# include "../errors/errors.h"
# include <stdio.h>
# include <stdlib.h>

typedef struct s_builtins_fn
{
	char	*name;
	int		(*fn)(t_list *, t_list *);
}	t_builtin;

t_builtin	get_builtin(t_command *command);

int			ft_echo(t_list *arguments, t_list *envs);
int			ft_pwd(t_list *arguments, t_list *envs);
int			ft_exit(t_list *arguments, t_list *envs);
int			ft_cd(t_list *arguments, t_list *envs);
int			ft_env(t_list *arguments, t_list *envs);
int			ft_export(t_list *arguments, t_list *envs);
int			ft_unset(t_list *arguments, t_list *envs);

/*utils fn for export*/
int			check_env_arg(char *arg, t_list *envs);
int			check_env_name(char *arg);
int			var_exists_in_envs(char *env_name, t_list *envs);
void		add_new_end_var(char *env_name, char *value, t_list **envs);
void		order_envs_list(t_list *envs);

/*utils fn for unset*/
int			check_if_valid(char *arg, t_list **envs);
#endif