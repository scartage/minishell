/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:32:09 by fsoares-          #+#    #+#             */
/*   Updated: 2023/11/11 17:08:25 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	new_len;
	int	start;

	new_len = ft_strlen(s1) - 1;
	while (new_len >= 0 && ft_strchr(set, s1[new_len]))
		new_len--;
	start = 0;
	while (ft_strchr(set, s1[start]))
	{
		start++;
		new_len--;
		if (s1[start - 1] == 0)
			break ;
	}
	return (ft_substr(s1, start, new_len + 1));
}
