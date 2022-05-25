/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:58:02 by lfilloux          #+#    #+#             */
/*   Updated: 2022/05/16 12:56:35 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	int	ft_isspace(char c)
{
	if (c == '\f' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == ' ')
		return (1);
	return (0);
}

long long	ft_atoi_exit(const char *str, int i)
{
	int			j;
	long		neg;
	long long	sum;

	neg = 1;
	sum = 0;
	j = 0;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			neg *= -1;
	while (str[i] && (ft_isspace(str[i]) || str[i] == '0'))
		i++;
	while (str[i] >= '0' && str[i] <= '9' && ++j)
	{
		sum = (sum * 10) + (str[i] - 48);
		i++;
	}
	while (str[i++])
		j++;
	return (sum * neg);
}

int	is_only_num(char *s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (2);
	if (s[i] == '-')
		i ++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i ++;
	}
	return (1);
}

static int	rigth_exit(t_cmd *cmd)
{
	long long	exit;

	exit = ft_atoi_exit(cmd->args[0], 0);
	exit = exit % 256;
	return ((int)exit);
}

void	our_exit(t_app *app, t_cmd *cmd, int pipe)
{
	if (!cmd->args[0])
	{
		g_status = 0;
		app->last_exit = 0;
		if (pipe == 0)
			close_minishell(app);
	}
	else if (cmd->args[0] && !cmd->args[1])
	{
		if (is_only_num(cmd->args[0]) == 1)
		{
			app->last_exit = rigth_exit(cmd);
			g_status = app->last_exit;
			if (pipe == 0)
				close_minishell(app);
		}
		else
			print_err_exit(app, cmd->args[0], 1, pipe);
	}
	else
		print_err_exit(app, cmd->args[0], 2, pipe);
}
