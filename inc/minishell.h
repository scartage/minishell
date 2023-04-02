/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:40:01 by scartage          #+#    #+#             */
/*   Updated: 2023/04/02 19:28:19 by scartage         ###   ########.fr       */
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


//Errores
void ft_perror(char *s);

//utils
int ft_strlen(char *s);

//get imput
int ft_get_imput(void);
#endif
