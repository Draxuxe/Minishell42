/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:09:28 by lfilloux          #+#    #+#             */
/*   Updated: 2022/05/24 15:18:26 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_name(char **str, int i)
{
	char	*name;

	if (str[i] && str[i][0])
		name = ft_strdup(str[i]);
	else
		name = NULL;
	return (name);
}

char	*find_cmd_name(t_app *app, char **str)
{
	char	*name;
	int		i;

	i = 0;
	name = NULL;
	while (str[i])
	{
		if (ft_strcmp_sensitive(str[i], ">") || ft_strcmp(str[i], ">>")
			|| ft_strcmp_sensitive(str[i], "<<") || ft_strcmp(str[i], "<"))
			i += 2;
		else if (str[i][0] == '>' || str[i][0] == '<')
			i ++;
		else
		{
			if (is_redir(str[i]))
				name = ft_substr(str[i], 0, is_redir(str[i]));
			else
				name = ft_strdup(str[i]);
			break ;
		}
	}
	if (!name)
		return (name);
	reset_str(&name, clean_args(name, app));
	return (name);
}

char	**get_full_name(char *name, char **args)
{
	char	**full;
	int		i;
	int		j;

	i = 0;
	j = 0;
	full = malloc(sizeof(char *) * (array_length(args) + 2));
	if (!full)
		return (NULL);
	if (name)
		full[j++] = name;
	while (args[i])
	{
		full[j++] = args[i];
		i ++;
	}
	full[j++] = NULL;
	return (full);
}
