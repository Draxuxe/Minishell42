/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleferra <aleferra@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:52:52 by aleferra          #+#    #+#             */
/*   Updated: 2022/04/29 12:59:11 by aleferra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_chain	*lexer(char *str)
{
	int		index;
	t_chain	*chain;

	chain = NULL;
	index = -1;
	while (str[++index])
		ft_add_back_chain(&chain, ft_add_new_chain(str[index], index));
	return (chain);
}
