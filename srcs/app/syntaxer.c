/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:08:18 by lfilloux          #+#    #+#             */
/*   Updated: 2022/05/11 11:43:54 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	right_token(t_token tk)
{
	if (tk == REDIR_IN)
		return (DIR_IN);
	else if (tk == REDIR_OUT)
		return (DIR_OUT);
	return (PIPE);
}

static int	checkquote(t_chain *token)
{
	int		mode;
	t_chain	*tmp;

	mode = 0;
	tmp = token;
	while (tmp)
	{
		if ((mode == 1 && tmp->token == QUOTE)
			|| (mode == 2 && tmp->token == DQUOTE))
			return (TRUE);
		if (tmp->token == QUOTE && mode == 0)
			mode = 1;
		else if (tmp->token == DQUOTE && mode == 0)
			mode = 2;
		if (mode == 0 && !tmp->next)
			return (TRUE);
		tmp = tmp->next;
	}
	return (-mode);
}

static int	otherquote(t_chain **token)
{
	int		mode;

	mode = 0;
	if ((*token)->token == QUOTE)
		mode = 1;
	if ((*token)->token == DQUOTE)
		mode = 2;
	if (!(*token)->next)
		return (-mode);
	(*token) = (*token)->next;
	while (*token)
	{
		if (mode == 1 && (*token)->token == QUOTE)
			return (TRUE);
		else if (mode == 2 && (*token)->token == DQUOTE)
			return (TRUE);
		if (!(*token)->next)
			return (-mode);
		*token = (*token)->next;
	}
	if (mode != 0)
		return (-mode);
	return (TRUE);
}

static int	check_token_error(t_chain *token)
{
	t_chain	*tmp;
	t_chain	*tmp1;

	tmp = token;
	tmp1 = tmp->next;
	if (tmp->next && tmp1->next && tmp1->next->next)
		return (check_for_three(tmp));
	if (tmp->next && tmp1->next)
		return (check_for_two(tmp));
	if (tmp->next)
	{
		if ((tmp->token == SPACE && tmp->prev->token == tmp->next->token
				&& tmp->prev->token != LITERAL) || ((tmp->token != LITERAL
					&& tmp->token != SPACE) && !tmp->next))
			return (right_token(tmp->prev->token));
		if (tmp->token == REDIR_IN && tmp->next->token == PIPE)
			return (PIPE);
	}
	if ((tmp->prev && (tmp->prev->token != LITERAL && tmp->prev->token != SPACE)
			&& !tmp->next && tmp->token != LITERAL)
		|| ((tmp->token != LITERAL && tmp->token != SPACE)
			&& !tmp->next))
		return (NEWLINE);
	return (0);
}

int	syntaxer(t_chain *tokens)
{
	t_chain	*tmp;
	int		err;

	tmp = tokens;
	err = 0;
	if (checkquote(tmp) != TRUE)
		return (checkquote(tmp));
	while (tmp)
	{
		err = check_token_error(tmp);
		if (err != 0)
			return (err);
		if ((tmp->token == QUOTE || tmp->token == DQUOTE)
			&& (otherquote(&tmp) != 1))
			return (otherquote(&tmp));
		tmp = tmp->next;
	}
	return (TRUE);
}
