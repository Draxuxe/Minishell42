/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:33:30 by aleferra          #+#    #+#             */
/*   Updated: 2022/05/18 14:53:49 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_space(char *str)
{
	size_t	i;
	int		nb;
	int		q;

	nb = 1;
	q = 0;
	i = 0;
	while (str[i])
	{
		if (q == 0 && (str[i] == '\'' || str[i] == '"'))
			q = str[i];
		else if (q == str[i])
			q = 0;
		if (q == 0 && str[i] == ' ')
			nb ++;
		i ++;
	}
	return (nb);
}

char	*clean_args(char *cmd, t_app *app)
{
	cmd = ft_expand_env(app, cmd);
	cmd = remove_q_or_dq(cmd);
	return (cmd);
}

char	*find_string(char *s, size_t *index)
{
	char	*new;
	int		q;
	int		start;

	q = 0;
	start = *index;
	while (s[*index])
	{
		if (q == 0 && (s[*index] == '\'' || s[*index] == '"'))
			q = s[*index];
		else if (q == s[*index])
			q = 0;
		if (s[*index] == ' ' && q == 0)
		{
			*index += 1;
			break ;
		}
		*index += 1;
	}
	new = ft_strtrim(ft_substr(s, start, *index - start), " ");
	return (new);
}

char	**split_quote(char *str)
{
	char	**split;
	int		index;
	int		nb_spaces;
	size_t	i;

	nb_spaces = count_space(str);
	split = malloc(sizeof(char *) * (nb_spaces + 1));
	if (!split)
		return (NULL);
	index = 0;
	i = 0;
	while (index < nb_spaces)
		split[index++] = find_string(str, &i);
	split[index] = NULL;
	return (split);
}
