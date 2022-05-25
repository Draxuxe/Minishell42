/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 10:55:59 by lfilloux          #+#    #+#             */
/*   Updated: 2022/05/10 10:59:58 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	reset_str(char **str, char *new)
{
	free(*str);
	*str = new;
}

char	*res_str(char **str, char *new)
{
	free(*str);
	*str = new;
	return (*str);
}

size_t	array_length(char **str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i ++;
	return (i);
}

t_token	is_a_pipe(size_t len, size_t i)
{
	if (i < len)
		return (PIPE);
	return (NONE);
}

int	is_builtin(char *s)
{
	if (ft_strcmp(s, "echo"))
		return (1);
	else if (ft_strcmp(s, "exit"))
		return (1);
	else if (ft_strcmp(s, "unset"))
		return (1);
	else if (ft_strcmp(s, "cd"))
		return (1);
	else if (ft_strcmp(s, "export"))
		return (1);
	else if (ft_strcmp(s, "env"))
		return (1);
	else if (ft_strcmp(s, "pwd"))
		return (1);
	return (0);
}
