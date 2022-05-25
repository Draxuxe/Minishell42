/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 10:08:35 by aleferra          #+#    #+#             */
/*   Updated: 2022/04/18 10:30:32 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	ft_token(char c)
{
	if (c == '&')
		return (AMPERSAND);
	else if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (REDIR_IN);
	else if (c == '>')
		return (REDIR_OUT);
	else if (c == '\'')
		return (QUOTE);
	else if (c == '"')
		return (DQUOTE);
	else if (c == ' ')
		return (SPACE);
	else
		return (LITERAL);
}

t_token	which_token(char *s)
{
	if (ft_strcmp_sensitive(s, "|>"))
		return (PIPE_OUT);
	else if (ft_strcmp_sensitive(s, "||>"))
		return (DPIPE_OUT);
	else if (ft_strcmp_sensitive(s, "|<"))
		return (PIPE_IN);
	else if (ft_strcmp_sensitive(s, "||<"))
		return (DPIPE_IN);
	else if (ft_strcmp_sensitive(s, ">"))
		return (REDIR_OUT);
	else if (ft_strcmp_sensitive(s, ">>"))
		return (APPEND);
	else if (ft_strcmp_sensitive(s, "|"))
		return (PIPE);
	else if (ft_strcmp_sensitive(s, "||"))
		return (DPIPE);
	else if (ft_strcmp_sensitive(s, "<"))
		return (REDIR_IN);
	if (ft_strcmp_sensitive(s, "&"))
		return (AMPERSAND);
	if (ft_strcmp_sensitive(s, "&&"))
		return (AND);
	else
		return (HERED);
}

int	is_token(char *s)
{
	size_t	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '|' || s[i] == '<' || s[i] == '>' || s[i] == '&')
			continue ;
		else
			return (FALSE);
	}
	return (TRUE);
}

t_token	arg_type(char *s, int *mode)
{
	if (*mode == 0 && (!is_token(s)))
	{
		*mode = 1;
		return (CMD);
	}
	else if (is_token(s))
	{
		*mode = 0;
		return (which_token(s));
	}
	else
		return (ARG);
}

int	is_env(char *str)
{
	int	index;

	index = 0;
	if (!str)
		return (-1);
	else if (str[index] == '$')
	{
		while (str[++index])
		{
			if (str[index] == '\'' || str[index] == '\"')
				return (index);
		}
		return (index);
	}
	else if (str[index] == '\"' && str[index + 1] && str[index + 1] == '$')
	{
		while (str[++index])
		{
			if (str[index] == '\"')
				return (index - 1);
		}
		return (index - 1);
	}
	return (-1);
}
