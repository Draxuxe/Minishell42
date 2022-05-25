/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_chain.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleferra <aleferra@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 10:16:02 by aleferra          #+#    #+#             */
/*   Updated: 2022/04/06 10:46:33 by aleferra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_chain	*ft_add_new_chain(char c, int index)
{
	t_chain	*chain;

	chain = malloc(sizeof(t_chain));
	if (!chain)
		return (NULL);
	chain->index = index;
	chain->token = ft_token(c);
	chain->next = NULL;
	chain->prev = NULL;
	return (chain);
}

void	ft_add_back_chain(t_chain **start, t_chain *new)
{
	t_chain	*tmp;

	if (!*start)
		*start = new;
	else
	{
		tmp = *start;
		while (tmp->next)
			tmp = tmp->next;
		new->prev = tmp;
		tmp->next = new;
	}
}
