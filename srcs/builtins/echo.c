/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:48:38 by aleferra          #+#    #+#             */
/*   Updated: 2022/06/07 14:57:18 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_an_opt(char *s)
{
	size_t		i;

	i = 0;
	if (!s)
		return (FALSE);
	if (s[0] != '-')
		return (FALSE);
	while (s[++i])
	{
		if (s[i] != 'n')
			return (FALSE);
	}
	return (TRUE);
}

void	ft_echo(t_app *app, t_cmd *cmd)
{
	int		opt;
	size_t	i;

	g_status = 0;
	app->last_exit = 0;
	if (!cmd->args || !cmd->args[0])
	{
		printf("\n");
		return ;
	}
	opt = 0;
	i = -1;
	while (is_an_opt(cmd->args[++i]))
		opt = 1;
	while (cmd->args[i] && !cmd->args[i][0] && i < array_length(cmd->args) - 1)
		i ++;
	while (cmd->args[i] && i < array_length(cmd->args) - 1)
	{
		printf("%s ", cmd->args[i]);
		i ++;
	}
	if (opt == 1 && cmd->args[i])
		printf("%s", cmd->args[i]);
	else if (cmd->args[i])
		printf("%s\n", cmd->args[i]);
}
