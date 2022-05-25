/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:17:53 by lfilloux          #+#    #+#             */
/*   Updated: 2022/05/12 14:53:32 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	which_input(t_app *app, char *file, char *name)
{
	int	input_fd;

	(void) name;
	if (file[0] == '$')
	{
		print_ambiguous_err(app, file);
		return (-1);
	}
	file = ft_expand_env(app, file);
	file = remove_q_or_dq(file);
	input_fd = open(file, O_RDONLY);
	if (input_fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_status = 1;
		input_fd = -2;
	}
	free(file);
	return (input_fd);
}

int	file_next_in(t_app *app, char *s, char *next)
{
	int		input_fd;

	input_fd = 1;
	if (next[0] == '$')
	{
		print_ambiguous_err(app, next);
		return (-1);
	}
	next = ft_expand_env(app, next);
	next = remove_q_or_dq(next);
	if (ft_strcmp_sensitive(s, "<"))
		input_fd = open(next, O_RDONLY);
	if (input_fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(next, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_status = 1;
		input_fd = -2;
	}
	free(next);
	return (input_fd);
}

int	next_r_in(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == '<')
		i ++;
	while (s[i] && s[i] != '<')
		i ++;
	return (i);
}

int	count_nb_redirs_in(char *s)
{
	int	i;
	int	count;
	int	start;

	i = 0;
	count = 0;
	while (i < (int)ft_strlen(s))
	{
		start = i;
		i += next_r_in(&s[start]);
		count ++;
	}
	return (count);
}
