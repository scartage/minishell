/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 19:11:24 by fsoares-          #+#    #+#             */
/*   Updated: 2023/10/12 19:34:21 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_lstremove(t_list **list, t_list *to_remove, void (*del)(void *))
{
	t_list	*prev;
	t_list	*temp;

	if (*list == NULL)
		return ;
	if (*list == to_remove)
	{
		*list = to_remove->next;
		ft_lstdelone(to_remove, del);
		return ;
	}
	prev = *list;
	temp = (*list)->next;
	while (temp && temp != to_remove)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp)
	{
		prev->next = temp->next;
		ft_lstdelone(to_remove, del);
	}
}
