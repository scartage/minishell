/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_case_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 14:43:00 by fsoares-          #+#    #+#             */
/*   Updated: 2022/04/09 14:52:45 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static char	to_lower_internal(unsigned int i, char c)
{
	(void)i;
	return (ft_tolower(c));
}

char	*to_lower_str(char *str)
{
	return (ft_strmapi(str, to_lower_internal));
}
