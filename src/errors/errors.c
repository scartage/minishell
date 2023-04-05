/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:00:31 by fsoares-          #+#    #+#             */
/*   Updated: 2023/04/05 16:09:22 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "libft.h"

void	free_globals(void)
{
	// TODO: Free all the global variables to avoid leaks
}

void	shell_error(char *reason)
{
	free_globals();
	terminate_with_error(reason);
}
