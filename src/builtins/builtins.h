/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:20:51 by scartage          #+#    #+#             */
/*   Updated: 2023/10/12 18:02:27 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft.h"

int echo(t_list *arguments, t_list *envs);
int pwd(t_list *arguments, t_list *envs);
int ft_exit(t_list *arguments, t_list *envs);
int ft_cd(t_list *arguments, t_list *envs);
int ft_env(t_list *arguments, t_list *envs);
#endif