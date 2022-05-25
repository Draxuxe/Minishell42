/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 10:03:52 by aleferra          #+#    #+#             */
/*   Updated: 2022/05/12 12:30:17 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	have_q_or_dq(char *str)
{
	int	index;

	index = -1;
	while (str[++index])
	{
		if (str[index] == '\'')
			return (1);
		else if (str[index] == '\"')
			return (2);
	}
	return (0);
}

int	count_quotes(char *s)
{
	int	quotes;
	int	i;
	int	mode;

	i = -1;
	quotes = 0;
	mode = 0;
	while (s[++i])
	{
		if ((s[i] == '\'' || s[i] == '"') && mode == 0)
			mode = s[i];
		else if (mode == s[i])
		{
			mode = 0;
			quotes ++;
		}
	}
	return (quotes * 2);
}

static t_bool	is_a_quote_here(char *s)
{
	if (ft_strchr(s, '\'') || s[0] == '\''
		|| ft_strchr(s, '"') || s[0] == '"')
		return (TRUE);
	return (FALSE);
}

char	*remove_q_or_dq(char *str)
{
	int		index;
	int		mode;
	int		start;
	char	*res;

	start = 0;
	index = -1;
	mode = 0;
	if (is_a_quote_here(str) == FALSE)
		return (str);
	res = malloc(sizeof(char) * (ft_strlen(str) - count_quotes(str) + 1));
	if (!res)
		return (NULL);
	while (str[++index])
	{
		if ((str[index] == '\'' || str[index] == '"') && mode == 0)
			mode = str[index];
		else if (mode == str[index])
			mode = 0;
		else if (mode != str[index])
			res[start++] = str[index];
	}
	free(str);
	res[start] = '\0';
	return (res);
}
