/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:17:10 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:16 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tmp;

	if (!lst || !f)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	if (!new)
	{
		ft_lstclear(&lst, del);
		return (NULL);
	}
	tmp = lst->next;
	while (lst)
	{
		tmp = ft_lstnew(f(tmp->content));
		if (!tmp)
		{
			ft_lstclear(&lst, del);
			ft_lstclear(&new, del);
			return (NULL);
		}
		lst = lst->next;
		ft_lstadd_back(&new, tmp);
	}
	return (new);
}
