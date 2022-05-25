/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:51:15 by lfilloux          #+#    #+#             */
/*   Updated: 2022/05/24 11:20:40 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_heredoc(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '<' && s[i + 1] == '<')
			return (TRUE);
	}
	return (FALSE);
}

int	handle_heredoc(int input_fd, t_app *app, char *del)
{
	int		p_fd[2];
	char	*line;
	char	*arg;
	int		test;

	test = dup(0);
	if (pipe(p_fd) == -1)
		return (-1);
	if (input_fd != 1)
		close(input_fd);
	input_fd = p_fd[0];
	while (1)
	{
		line = readline(HEREDOC_PROMPT_SYMBOL);
		if (!line)
			break ;
		if (ft_strcmp(line, del))
			break ;
		arg = ft_strjoin(find_env(line, app), "\n");
		ft_putstr_fd(arg, p_fd[1]);
		free_both(line, arg);
	}
	handle(line, p_fd, test, app);
	return (input_fd);
}

int	get_file_heredoc(t_app *app, char **split, char *next)
{
	int		input_fd;
	int		j;
	char	*file;

	j = -1;
	input_fd = 1;
	while (split[++j])
	{
		file = ft_strtrim(ft_strdup(split[j]), "<");
		if (!file[0] || ft_strcmp(split[j], "<<"))
			reset_str(&file, ft_strdup(next));
		input_fd = handle_heredoc(input_fd, app, file);
		if (file)
			free(file);
	}
	free_array(split);
	return (input_fd);
}

int	read_heredoc(t_app *app, char **s, size_t i)
{
	int		input_fd;
	char	**split;

	input_fd = 1;
	if (ft_strcmp_sensitive(s[i], "<<"))
	{
		input_fd = handle_heredoc(input_fd, app, s[i + 1]);
		return (input_fd);
	}
	if (ft_strchr(s[i], '<') || (s[i][0] == '<' && s[i][1] == '<'))
	{
		if (i == 0)
			split = split_redir_in(ft_substr(s[i], ft_strchr(s[i], '<'),
						ft_strlen(s[i])), s[i + 1]);
		else
			split = split_redir_in(ft_strdup(s[i]), s[i + 1]);
		input_fd = get_file_heredoc(app, split, s[i + 1]);
	}
	return (input_fd);
}
