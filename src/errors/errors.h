/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:00:29 by fsoares-          #+#    #+#             */
/*   Updated: 2023/04/05 18:02:31 by fsoares-         ###   ########.fr       */
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

#endif