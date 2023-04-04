/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:26:48 by fsoares-          #+#    #+#             */
/*   Updated: 2022/02/15 21:23:05 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	t_byte	*mem;

	mem = (t_byte *)s;
	while (n--)
	{
		if (*mem == (t_byte)c)
			return (mem);
		mem++;
	}
	return (NULL);
}
