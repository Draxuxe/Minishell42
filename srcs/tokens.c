/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 10:36:09 by lfilloux          #+#    #+#             */
/*   Updated: 2022/05/11 11:44:51 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_for_three(t_chain *tmp)
{
	if (tmp->token == REDIR_IN && tmp->next->token == SPACE
		&& tmp->next->next->token == REDIR_IN)
		return (DIR_IN);
	if (tmp->token == REDIR_OUT && tmp->next->token == SPACE
		&& tmp->next->next->token == REDIR_OUT)
		return (DIR_OUT);
	if (tmp->token == AMPERSAND && (tmp->next->token != LITERAL
			&& tmp->next->token != AMPERSAND))
		return (AMPER);
	if (tmp->token == AMPERSAND && tmp->next->token == AMPERSAND)
		return (ANDS);
	if (tmp->token == REDIR_IN && tmp->next->token == REDIR_IN
		&& tmp->next->next->token == REDIR_IN)
		return (DDIR_IN);
	if (tmp->token == REDIR_OUT && tmp->next->token == REDIR_OUT
		&& tmp->next->next->token == REDIR_OUT)
		return (DDIR_OUT);
	if (tmp->token == PIPE && tmp->next->token == PIPE)
		return (DPIPE);
	return (0);
}

int	check_for_two(t_chain *tmp)
{
	if (tmp->token == REDIR_IN && tmp->next->token == PIPE
		&& tmp->next->next->token == PIPE)
		return (DPIPE);
	if (tmp->token == PIPE && tmp->next->token == REDIR_IN
		&& tmp->next->next->token == PIPE)
		return (PIPE);
	if (tmp->token == REDIR_IN && tmp->next->token == REDIR_IN
		&& tmp->next->next->token == REDIR_IN)
		return (DIR_IN);
	if (tmp->token == REDIR_OUT && tmp->next->token == REDIR_OUT
		&& tmp->next->next->token == REDIR_OUT)
		return (DIR_OUT);
	if (tmp->token == PIPE && tmp->next->token == PIPE
		&& tmp->next->next->token == PIPE)
		return (DPIPE);
	return (0);
}
