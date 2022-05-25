/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:07:12 by aleferra          #+#    #+#             */
/*   Updated: 2022/05/09 15:02:17 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	is_real_heredoc_redir(char *s, int *mode)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == *mode)
			*mode = 0;
		else if (s[i] == '\'' && *mode == 0)
			*mode = s[i];
		else if (s[i] == '"' && *mode == 0)
			*mode = s[i];
		if (s[i] == '<' && s[i + 1] == '<' && *mode == 0)
			return (TRUE);
		i ++;
	}
	return (FALSE);
}

t_bool	is_real_in_redir(char *s, int *mode)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == *mode)
			*mode = 0;
		else if (s[i] == '\'' && *mode == 0)
			*mode = s[i];
		else if (s[i] == '"' && *mode == 0)
			*mode = s[i];
		if (s[i] == '<' && *mode == 0)
			return (TRUE);
		i ++;
	}
	return (FALSE);
}

t_bool	is_real_out_redir(char *s, int *mode)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == *mode)
			*mode = 0;
		else if (s[i] == '\'' && *mode == 0)
			*mode = s[i];
		else if (s[i] == '"' && *mode == 0)
			*mode = s[i];
		if (s[i] == '>' && *mode == 0)
			return (TRUE);
		i ++;
	}
	return (FALSE);
}

int	is_redir(char *s)
{
	size_t	i;
	int		q;

	i = 0;
	q = 0;
	while (s[i])
	{
		if (q == 0 && (s[i] == '\'' || s[i] == '"'))
			q = s[i];
		else if (s[i] == q)
			q = 0;
		if ((s[i] == '>' || s[i] == '<') && q == 0)
			return (i);
		i ++;
	}
	return (0);
}
