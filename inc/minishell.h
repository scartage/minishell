/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:40:01 by scartage          #+#    #+#             */
/*   Updated: 2023/04/04 17:10:21 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>  //para el write, isatty
#include <stdlib.h> //para el exit
#include <string.h>	//para el strcmp (temporal)

#include <readline/readline.h>
#include <readline/history.h>

//get imput
int ft_get_imput(void);
#endif
