/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:27:49 by aleferra          #+#    #+#             */
/*   Updated: 2022/05/10 11:32:24 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_chain(t_chain *tokens)
{
	t_chain	*tmp;
	t_chain	*clear;

	tmp = tokens;
	while (tmp)
	{
		clear = tmp;
		tmp = tmp->next;
		free(clear);
	}
}

static void	check_err(int err)
{
	if (err != 0 && err != 1)
		g_status = 2;
}

void	catch_error(int err, t_chain *tokens)
{
	check_err(err);
	if (err == QQUOTES)
		ft_putstr_fd("Minishell: syntax error near unclosed quote `''\n", 2);
	else if (err == DQUOTES)
		ft_putstr_fd("Minishell: syntax error near unclosed quote`\"'\n", 2);
	else if (err == PIPE)
		ft_putstr_fd("Minishell: syntax error near unexpected token `|'\n", 2);
	else if (err == DPIPE)
		ft_putstr_fd("Minishell: syntax error near unexpected token `||'\n", 2);
	else if (err == DIR_OUT)
		ft_putstr_fd("Minishell: syntax error near unexpected token `>'\n", 2);
	else if (err == DDIR_OUT)
		ft_putstr_fd("Minishell: syntax error near unexpected token `>>'\n", 2);
	else if (err == DIR_IN)
		ft_putstr_fd("Minishell: syntax error near unexpected token `<'\n", 2);
	else if (err == DDIR_IN)
		ft_putstr_fd("Minishell: syntax error near unexpected token `<<'\n", 2);
	else if (err == AMPER)
		ft_putstr_fd("Minishell: syntax error near unexpected token `&'\n", 2);
	else if (err == ANDS)
		ft_putstr_fd("Minishell: syntax error near unexpected token `&&'\n", 2);
	else if (err == NEWLINE)
		ft_putstr_fd("Minishell: syntax error near unexpected token `newline'\n",
			2);
	free_chain(tokens);
}
