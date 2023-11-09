/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:09:25 by fsoares-          #+#    #+#             */
/*   Updated: 2023/11/07 20:35:04 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

void	free_token(void *token_)
{
	t_token	*token;

	token = token_;
	free(token->value);
	free(token);
}

t_token	*classify(char *str)
{
	t_token	*token;

	token = protected_malloc(sizeof(t_token));
	token->value = ft_strdup(str);
	if (str[0] == '|')
		token->type = PIPE;
	else if (str[0] == '>' || str[0] == '<')
		token->type = REDIR;
	else
		token->type = ARGUMENT;
	return (token);
}

t_list	*classify_tokens(t_list *tokens)
{
	t_list	*result;

	result = ft_lstmap(tokens, (void *(*)(void *))classify, free_token);
	ft_lstclear(&tokens, free);
	return (result);
}
