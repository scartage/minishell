/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:00:29 by fsoares-          #+#    #+#             */
/*   Updated: 2023/10/20 19:05:22 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

/** Frees all the variables that are stored in the global variables */
void	free_globals(void);

/** 
 * Shows the error and terminates the shell with the reason passed as 
 * argument 
 * 
 * @param reason The reason to display on the terminal
 */
void	shell_error(char *reason);

/**
 * Shows the error and the generated perror, and aborts the shell, cleaning
 * the global variables
 * 
 * @param reason The reason to display on the terminal
 */
void	abort_perror(char *reason);

/**
 * Shows the error and exit. Used in the main
 * 
 * @param s The reason to display on the terminal
 */
void	ft_error(char *s);

/**
 * Show error in checkers for input
 * if command is NULL then the command is ommited from the error
 * it will output the error as "minishell: <command>: <msg>"
 * if command is NULL, then it will output: "minishell: <msg>"
 */
void	show_error(char *command, char *msg);
#endif