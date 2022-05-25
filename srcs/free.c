/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 17:10:47 by aleferra          #+#    #+#             */
/*   Updated: 2022/05/18 14:29:14 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*last;
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		last = tmp;
		free_array(tmp->args);
		free_array(tmp->args_nu);
		if (tmp->name)
			free(tmp->name);
		free(tmp->name_nu);
		free(tmp->full);
		tmp = tmp->next;
		free(last);
	}
	free(tmp);
}

void	free_array(char **array)
{
	size_t	i;

	i = -1;
	if (!array)
		return ;
	while (array[++i])
		free(array[i]);
	free(array);
}

void	free_end(char *line, t_cmd *command)
{
	if (line)
		free(line);
	free_cmd(command);
}

void	free_both(char *line, char *arg)
{
	if (line)
		free(line);
	if (arg)
		free(arg);
}
