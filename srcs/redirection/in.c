/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:08:49 by aleferra          #+#    #+#             */
/*   Updated: 2022/05/24 15:21:16 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**split_redir_in(char *s, char *next)
{
	char	**dest;
	int		index;
	int		i;
	int		start;

	dest = malloc(sizeof(char *) * (count_nb_redirs_in(s) + 1));
	if (!dest)
		return (NULL);
	index = 0;
	i = ft_strchr(s, '<');
	while (i < (int)ft_strlen(s) - 1)
	{
		start = i;
		i += next_r_in(&s[start]);
		dest[index] = ft_substr(s, start, i - start);
		if (ft_strcmp(dest[index], "<") || ft_strcmp(dest[index], "<<"))
			dest[index] = ft_strjoin_properly(dest[index], ft_strdup(next));
		index ++;
	}
	dest[index] = NULL;
	free(s);
	return (dest);
}

int	get_right_file(t_app *app, char **split, char *name, char *next)
{
	int		input_fd;
	char	*file;
	int		j;

	j = -1;
	input_fd = 1;
	while (split[++j])
	{
		file = ft_strtrim(ft_strdup(split[j]), "<");
		if (!file[0] || ft_strcmp(split[j], "<"))
			reset_str(&file, ft_strdup(next));
		if (file[0] == '&')
		{
			input_fd = dup(ft_atoi(&file[1]));
			if (input_fd == -1)
				print_fd_err(app, &file[1]);
		}
		else
			input_fd = which_input(app, file, name);
		free(file);
	}
	free_array(split);
	return (input_fd);
}

int	read_redir_in(t_app *app, char **s, char *name, size_t i)
{
	int		input_fd;
	char	**split;

	input_fd = 1;
	if (ft_strcmp_sensitive(s[i], "<"))
		return (file_next_in(app, s[i], s[i + 1]));
	if (ft_strchr(s[i], '<') || s[i][0] == '<')
	{
		if (i == 0)
			split = split_redir_in(ft_substr(s[i], ft_strchr(s[i], '<'),
						ft_strlen(s[i])), s[i + 1]);
		else
			split = split_redir_in(ft_strdup(s[i]), s[i + 1]);
		input_fd = get_right_file(app, split, name, s[i + 1]);
	}
	return (input_fd);
}

int	find_redir_in(t_app *app, char **s, char *name)
{
	size_t	i;
	int		mode;
	int		last_input_fd;
	int		input;

	i = -1;
	last_input_fd = 1;
	input = 1;
	mode = 0;
	while (s[++i])
	{
		if (is_real_heredoc_redir(s[i], &mode))
			last_input_fd = read_heredoc(app, s, i);
		else if (is_real_in_redir(s[i], &mode))
		{
			last_input_fd = read_redir_in(app, s, name, i);
			if (last_input_fd == -1 || last_input_fd == -2)
				return (last_input_fd);
		}
		if (name && is_builtin(name))
			last_input_fd = 1;
	}
	return (last_input_fd);
}
