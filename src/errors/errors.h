/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:00:29 by fsoares-          #+#    #+#             */
/*   Updated: 2023/04/05 16:09:04 by fsoares-         ###   ########.fr       */
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

#endif