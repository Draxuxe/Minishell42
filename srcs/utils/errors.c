/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:07:14 by lfilloux          #+#    #+#             */
/*   Updated: 2022/05/24 17:55:41 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_err_cd(t_app *app, char *cmd, int err, int pipe)
{
	char	*error;

	if (err == 5)
	{
		ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
		app->last_exit = 1;
		g_status = 1;
	}
	else if (err != 0)
	{
		error = ft_strjoin("Minishell: cd: ", cmd);
		perror(error);
		if (pipe == 0)
		{
			set_env(app, "OLDPWD", ft_strdup(app->oldpwd));
			set_env(app, "PWD", ft_strdup(app->pwd));
		}
		g_status = 1;
		app->last_exit = 1;
		free(error);
	}
	else if (err == 0)
		g_status = 0;
}

void	print_err_exit(t_app *app, char *cmd, int err, int pipe)
{
	if (err == 1 && pipe == 0)
	{
		ft_putstr_fd("exit\nminishell: exit: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		if (pipe == 0)
			app->last_exit = 255;
		else
			app->last_exit = 1;
	}
	else if (err == 2 && pipe == 0)
	{
		ft_putstr_fd("exit\nminishell: exit: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": too many arguments\n", 2);
		if (pipe == 0)
			app->last_exit = 1;
		else
			app->last_exit = 1;
	}
	if (pipe == 0)
		app->running = FALSE;
}

void	print_err_token(t_app *app)
{
	app->last_exit = 1;
	ft_putstr_fd("Minishell: A token isn't supported by our program!\n", 2);
}

void	print_fd_err(t_app *app, char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": Bad file descriptor\n", 2);
	app->last_exit = 1;
}

void	print_ambiguous_err(t_app *app, char *name)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ambiguous redirection\n", 2);
	g_status = 1;
	app->err = 1;
}
