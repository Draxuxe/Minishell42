/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:34:22 by aleferra          #+#    #+#             */
/*   Updated: 2022/05/24 16:18:49 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_args_clean(t_app *app, char **s, int index, size_t i)
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
			reset_str(&args[index], clean_args(args[index], app));
			index ++;
		}
	}
	args[index] = NULL;
	return (args);
}
