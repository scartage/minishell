/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 17:42:22 by fsoares-          #+#    #+#             */
/*   Updated: 2022/04/09 19:10:59 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*unquote(char *word)
{
	char	*res;
	int		len;
	int		i;
	int		j;

	if (word[0] != '\'' && word[0] != '"')
	{
		res = ft_strdup(word);
		if (res == NULL)
			terminate_with_error("Failed ft_strdup");
		return (res);
	}
	len = ft_strlen(word);
	res = protected_malloc(len);
	i = 1;
	j = 0;
	while (i < len - 1)
	{
		if (word[i] == '\\' && word[i + 1] == word[0])
			i++;
		res[j++] = word[i++];
	}
	res[j] = 0;
	return (res);
}
