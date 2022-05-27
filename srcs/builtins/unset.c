/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 11:24:49 by lfilloux          #+#    #+#             */
/*   Updated: 2022/05/27 13:24:54 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	unset_err(t_app *app, char *str)
{
	if (!str[0])
		ft_putstr_fd("unset: `': not a valid identifier\n", STDERR_FILENO);
	else
	{
		ft_putstr_fd("unset: '", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	g_status = 1;
	app->last_exit = 1;
}

static int	right_env(char *arg, t_env *tmp, t_env *last, t_env **env)
{
	if (ft_strcmp_sensitive(tmp->key, arg))
	{
		if (last)
			last->next = tmp->next;
		else if (!last)
			*env = (*env)->next;
		free_env(tmp);
		return (1);
	}
	return (0);
}

void	find_existence_tmp(t_app **app, t_env *tmp, char *arg, int pipe)
{
	while (tmp->next)
	{
		if (pipe == 0)
		{
			if (right_env(arg, tmp->next, tmp, &(*app)->env))
				break ;
		}
		tmp = tmp->next;
	}
	if (!tmp)
	{
		(*app)->last_exit = 1;
		g_status = 1;
	}
}

static int	init_var(t_app **app)
{
	(*app)->last_exit = 0;
	g_status = 0;
	return (0);
}

void	unset(t_cmd *cmd, t_app **app, int pipe)
{
	t_env	*tmp;
	size_t	i;
	int		err;

	err = init_var(app);
	i = -1;
	while (cmd->args[++i] && (*app)->env)
	{
		tmp = (*app)->env;
		if (cmd->args[i] && (!cmd->args[i][0]
			|| (!ft_isalpha(cmd->args[i][0]) && cmd->args[i][0] != '_')))
		{
			unset_err(*app, cmd->args[i]);
			continue ;
		}
		if (ft_strcmp_sensitive(tmp->key, cmd->args[i]))
		{
			if (pipe == 0)
				(*app)->env = (*app)->env->next;
			free_env(tmp);
		}
		else
			find_existence_tmp(app, tmp, cmd->args[i], pipe);
	}
}
