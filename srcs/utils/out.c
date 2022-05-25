/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:17:50 by lfilloux          #+#    #+#             */
/*   Updated: 2022/05/18 14:01:46 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_last_outredir(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if ((s[i] == '>' && s[i + 1] != '>'))
			return (i);
		else if ((s[i] == '>' && s[i + 1] == '>'))
			return (i + 1);
	}
	return (0);
}

int	file_next_out(t_app *app, char *s, char *next)
{
	int	output_fd;

	output_fd = 1;
	if (next[0] == '$')
	{
		print_ambiguous_err(app, next);
		return (-1);
	}
	next = clean_args(next, app);
	if (ft_strcmp_sensitive(s, ">"))
	{
		output_fd = open(next,
				O_CREAT | O_RDWR | O_TRUNC, S_IRUSR
				| S_IRGRP | S_IWGRP | S_IWUSR);
	}
	else if (ft_strcmp_sensitive(s, ">>"))
	{
		output_fd = open(next,
				O_CREAT | O_RDWR | O_APPEND, S_IRUSR
				| S_IRGRP | S_IWGRP | S_IWUSR);
	}
	free(next);
	return (output_fd);
}

int	which_output(t_app *app, char *s, char *file)
{
	int	output_fd;

	output_fd = 1;
	if (file[0] == '$')
	{
		print_ambiguous_err(app, file);
		return (-1);
	}
	file = clean_args(file, app);
	if (s[0] == '>' && s[1] == '>')
	{
		output_fd = open(file,
				O_CREAT | O_RDWR | O_APPEND, S_IRUSR
				| S_IRGRP | S_IWGRP | S_IWUSR);
	}
	else
	{
		output_fd = open(file,
				O_CREAT | O_RDWR | O_TRUNC, S_IRUSR
				| S_IRGRP | S_IWGRP | S_IWUSR);
	}
	free(file);
	return (output_fd);
}

int	next_r_out(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == '>')
		i ++;
	while (s[i] && s[i] != '>')
		i ++;
	return (i);
}

int	count_nb_redirs(char *s)
{
	int	i;
	int	count;
	int	start;

	i = 0;
	count = 0;
	while (i < (int)ft_strlen(s))
	{
		start = i;
		i += next_r_out(&s[start]);
		count ++;
	}
	return (count);
}
