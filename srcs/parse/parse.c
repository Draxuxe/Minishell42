/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleferra <aleferra@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:25:12 by aleferra          #+#    #+#             */
/*   Updated: 2022/05/11 10:58:15 by aleferra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_count_word(char *str)
{
	int	index;
	int	mots;

	index = 0;
	mots = 1;
	while (str[++index])
	{
		if (str[index] == ' ')
		{
			while (str[index] && str[++index] == ' ')
				;
			mots++;
		}
		if (str[index] && str[index] == '"')
		{
			while (str[index] && str[++index] != '"')
				;
		}
		if (str[index] && str[index] == '\'')
		{
			while (str[index] && str[++index] != '\'')
				;
		}
	}
	return (mots);
}

void	find_arg(char *s, size_t *start, size_t *index)
{
	int	q;

	q = 0;
	*start = *index;
	while (s[*index])
	{
		if (q == 0 && (s[*index] == '\'' || s[*index] == '"'))
		{
			q = s[*index];
			*index += 1;
		}
		if (s[*index] == ' ' && q == 0)
			return ;
		if (q == s[*index] && s[*index + 1] && s[*index + 1] == ' ')
		{
			*index += 1;
			return ;
		}
		if (q == s[*index] && s[*index + 1] && s[*index + 1] != ' ')
			q = 0;
		*index += 1;
	}
}

char	**parse_quotes(char *s)
{
	char	**args;
	size_t	i;
	size_t	index;
	size_t	start;

	args = malloc(sizeof(char *) * (ft_count_word(s) + 1));
	if (!args)
		return (NULL);
	i = 0;
	index = 0;
	start = 0;
	while (s[index] && index < ft_strlen(s))
	{
		while (s[index] == ' ')
			index ++;
		find_arg(s, &start, &index);
		args[i] = ft_substr(s, start, index - start);
		i ++;
	}
	args[i] = NULL;
	return (args);
}

t_bool	is_all_env(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->args[++i])
	{
		if (!cmd->args[i][0] && cmd->args_nu[i][0] == '$')
			;
		else
			return (FALSE);
	}
	return (TRUE);
}
