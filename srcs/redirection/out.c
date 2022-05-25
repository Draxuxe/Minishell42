/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:01:47 by aleferra          #+#    #+#             */
/*   Updated: 2022/05/18 14:15:31 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**split_redir(char *s, char *next)
{
	char	**dest;
	int		index;
	int		i;
	int		start;

	dest = malloc(sizeof(char *) * (count_nb_redirs(s) + 1));
	if (!dest)
		return (NULL);
	index = 0;
	i = ft_strchr(s, '>');
	while (i < (int)ft_strlen(s))
	{
		start = i;
		i += next_r_out(&s[start]);
		dest[index] = ft_substr(s, start, i - start);
		if (ft_strcmp(dest[index], ">") || ft_strcmp(dest[index], ">>"))
			dest[index] = ft_strjoin_properly(dest[index],
					ft_substr(next, 0, ft_strchr(next, '>')));
		index ++;
	}
	dest[index] = NULL;
	free(s);
	return (dest);
}

int	get_right_file_out(t_app *app, char **split, char *next)
{
	int		j;
	int		output_fd;
	int		out;
	char	*file;

	j = -1;
	out = 1;
	while (split[++j])
	{
		file = ft_strtrim(ft_strdup(split[j]), ">");
		if (!file[0] || ft_strcmp(split[j], ">") || ft_strcmp(split[j], ">>"))
			reset_str(&file, ft_strdup(next));
		if (file[0] == '&')
			is_valid_fd(app, file);
		else
			out = which_output(app, split[j], file);
		free(file);
		if (out == -1)
			break ;
		output_fd = out;
	}
	free_array(split);
	return (output_fd);
}

int	create_redir_out(t_app *app, char **s, size_t i)
{
	int		output_fd;
	char	**split;

	output_fd = 1;
	if (ft_strcmp_sensitive(s[i], ">") || ft_strcmp_sensitive(s[i], ">>"))
		return (file_next_out(app, s[i], s[i + 1]));
	else if (ft_strchr(s[i], '>') || s[i][0] == '>')
	{
		if (i == 0)
			split = split_redir(ft_substr(s[i], ft_strchr(s[i], '>'),
						ft_strlen(s[i])), s[i + 1]);
		else
			split = split_redir(ft_strdup(s[i]), s[i + 1]);
		output_fd = get_right_file_out(app, split, s[i + 1]);
	}
	return (output_fd);
}

t_bool	is_real_redir(char *s, int *mode)
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

int	find_redir_out(t_app *app, char **s)
{
	size_t	i;
	int		mode;
	int		last_output_fd;
	int		output;

	i = -1;
	last_output_fd = 1;
	output = 1;
	mode = 0;
	while (s[++i])
	{
		if (is_real_redir(s[i], &mode))
			output = create_redir_out(app, s, i);
		if (output == -1)
			break ;
		last_output_fd = output;
	}
	return (last_output_fd);
}
