/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:35:27 by lfilloux          #+#    #+#             */
/*   Updated: 2022/05/18 15:02:39 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_end(char *str)
{
	int	end;

	end = 0;
	while (str[++end])
	{
		if (str[end] == '\'' || str[end] == '\"' || str[end] == '$'
			|| str[end] == '/' || str[end] == '=')
			break ;
	}
	return (end);
}

static void	which_quote(char *s, int *i, int *mode)
{
	while (s[*i] && s[*i] != '$')
	{
		if (s[*i] == '"' && *mode == 0)
			*mode = 2;
		else if (s[*i] == '\'' && *mode == 0)
			*mode = 1;
		else if ((s[*i] == '\'' && *mode == 1)
			|| (s[*i] == '"' && *mode == 2))
			*mode = 0;
		*i += 1;
	}
}

static char	*expand_dest(t_app *app, char *str, int i, int mode)
{
	char	*env;

	env = ft_substr(str, i, find_end(&str[i]));
	if (mode != 1)
		env = get_env(app, env);
	return (env);
}

void	expand_fd(t_cmd *cmd)
{
	if (cmd->input_fd > 1)
		dup2(cmd->input_fd, STDIN_FILENO);
	else if (cmd->pre)
		dup2 (cmd->pre->pipe[0], 0);
	if (cmd->output_fd > 1)
		dup2(cmd->output_fd, STDOUT_FILENO);
	else if (cmd->next)
		dup2 (cmd->pipe[1], 1);
}

char	*ft_expand_env(t_app *app, char *str)
{
	int		mode;
	int		i;
	char	*dest;
	int		start;

	mode = 0;
	i = 0;
	dest = NULL;
	if (!ft_strchr(str, '$') && str[0] != '$')
		return (ft_strdup(str));
	while (i < (int)ft_strlen(str))
	{
		start = i;
		which_quote(str, &i, &mode);
		if (!dest)
			dest = ft_substr(str, start, i - start);
		else
			dest = ft_strjoin_properly(dest, ft_substr(str, start, i - start));
		if (str[i] == '$')
		{
			dest = ft_strjoin_properly(dest, expand_dest(app, str, i, mode));
			i += find_end(&str[i]);
		}
	}
	return (dest);
}
