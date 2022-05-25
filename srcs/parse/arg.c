/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:12:32 by aleferra          #+#    #+#             */
/*   Updated: 2022/05/24 15:22:18 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_args_count(char **s)
{
	int	i;
	int	count;

	i = -1;
	count = -1;
	while (s[++i])
	{
		if (s[i][0] == '<' || s[i][0] == '>')
			continue ;
		else if (ft_strcmp(s[i], ">") || ft_strcmp(s[i], ">>"))
		{
			i ++;
			continue ;
		}
		count ++;
	}
	return (count);
}

int	check_redir(char *s, size_t *i)
{
	if (s[0] == '>' || s[0] == '<')
	{
		if (ft_strcmp(s, ">") || ft_strcmp(s, "<")
			|| ft_strcmp_sensitive(s, ">>")
			|| ft_strcmp_sensitive(s, "<<"))
			*i += 1;
		return (1);
	}
	return (0);
}

size_t	last_redir(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if ((s[i] == '>' && s[i + 1] != '>')
			|| (s[i] == '<' && s[i + 1] != '<'))
			return (i);
		else if ((s[i] == '>' && s[i + 1] == '>')
			|| (s[i] == '<' && s[i + 1] == '<'))
			return (i + 1);
	}
	return (0);
}

t_bool	is_only_redir(char *s)
{
	if (ft_strcmp_sensitive(s, ">"))
		return (TRUE);
	else if (ft_strcmp_sensitive(s, ">>"))
		return (TRUE);
	else if (ft_strcmp_sensitive(s, "<"))
		return (TRUE);
	else if (ft_strcmp_sensitive(s, "<<"))
		return (TRUE);
	return (FALSE);
}

char	**get_args(t_app *app, char **s)
{
	int		index;
	char	**args;
	size_t	i;

	i = 0;
	index = 0;
	while (is_only_redir(s[i]))
		i += 2;
	while (s[i][0] == '>' || s[i][0] == '<')
		i += 1;
	args = get_args_clean(app, s, index, i);
	return (args);
}
