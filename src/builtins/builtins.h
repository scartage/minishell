/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:20:51 by scartage          #+#    #+#             */
/*   Updated: 2023/11/07 19:36:20 by scartage         ###   ########.fr       */
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

bool		is_builtin(t_command *command);
bool		is_special_builtin(t_command *command);

int			call_builtin(t_list *args, t_list *envs,
				int last_st, bool is_1_com);

int			ft_echo(t_list *arguments);
int			ft_pwd(void);
int			ft_exit(t_list *args, int last_st, bool is_1_com);
int			ft_cd(t_list *arguments, t_list *envs);
int			ft_env(t_list *arguments, t_list *envs);
int			ft_export(t_list *arguments, t_list *envs);
int			ft_unset(t_list *arguments, t_list *envs);

/*utils fn for echo*/
bool		echo_is_valid_option(char *argument);

/*utils fn for export*/
int			check_env_arg(char *arg, t_list *envs);
int			check_env_name(char *arg);
int			var_exists_in_envs(char *env_name, t_list *envs);
void		add_new_end_var(char *env_name, char *value, t_list **envs);
void		update_env_content(char *env_name, char *value, t_list *envs);
void		order_envs_list(t_list *envs);

/*utils fn for unset*/
int			remove_if_valid(char *arg, t_list **envs);
#endif