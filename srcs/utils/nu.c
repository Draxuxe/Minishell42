/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nu.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleferra <aleferra@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:33:50 by aleferra          #+#    #+#             */
/*   Updated: 2022/05/10 11:35:36 by aleferra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_cmd_name_nu(t_app *app, char **str)
{
	char	*name;

	(void) app;
	if (ft_strcmp_sensitive(str[0], ">") || ft_strcmp_sensitive(str[0], ">>")
		|| ft_strcmp_sensitive(str[0], "<<"))
		name = get_name(str, 2);
	else if (str[0][0] == '>' || (str[0][0] == '<' && str[0][1] == '<'))
		name = get_name(str, 1);
	else if (is_redir(str[0]))
		name = ft_substr(str[0], 0, is_redir(str[0]));
	else
		name = ft_strdup(str[0]);
	if (!name)
		return (name);
	return (name);
}

char	**get_args_nu_no_clean(char **s, int index, size_t i)
{
	char	**args;

	args = malloc(sizeof(char *) * (get_args_count(s) + 1));
	if (!args)
		return (NULL);
	if (s[i])
	{
		while (s[++i])
		{
			if (check_redir(s[i], &i) == 1)
				continue ;
			if (is_redir(s[i]) && (s[i][0] != '<' || s[i][0] != '>'))
			{
				args[index] = ft_substr(s[i], 0, is_redir(s[i]));
				if (last_redir(s[i]) == (ft_strlen(s[i]) - 1))
					i ++;
			}
			else
				args[index] = ft_strdup(s[i]);
			index++;
		}
	}
	args[index] = NULL;
	return (args);
}

char	**get_args_nu(char **s)
{
	int		index;
	char	**args;
	size_t	i;

	i = 0;
	index = 0;
	if (is_only_redir(s[0]))
		i = 2;
	else if (s[0][0] == '>' || s[0][0] == '<')
		i = 1;
	args = get_args_nu_no_clean(s, index, i);
	return (args);
}
