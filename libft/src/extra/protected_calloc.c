/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_calloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:30:35 by fsoares-          #+#    #+#             */
/*   Updated: 2023/02/01 19:54:26 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../../libft.h"

void	terminate_with_error(char *message)
{
	write(2, "Error: ", 7);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	exit(1);
}

void	*protected_calloc(size_t count, size_t size)
{
	void	*res;

	res = ft_calloc(count, size);
	if (!res)
		terminate_with_error("Failed calloc");
	return (res);
}

void	*protected_malloc(size_t size)
{
	void	*res;

	res = malloc(size);
	if (!res)
		terminate_with_error("Failed malloc");
	return (res);
}
