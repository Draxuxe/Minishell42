/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:59:11 by lfilloux          #+#    #+#             */
/*   Updated: 2022/06/10 12:03:33 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_oldpwd(t_app *app, int pipe)
{
	char	*new;
	char	*oldpwd;

	if (pipe == 0)
	{		
		oldpwd = get_env_cd(app, ft_strdup("$OLDPWD"));
		if (!oldpwd)
		{
			new = ft_strjoin_properly(ft_strdup("OLDPWD="),
					get_env(app, ft_strdup("$PWD")));
			ft_add_back_env(&app->env, ft_add_new_env(new));
			free(new);
		}
		free(oldpwd);
	}
}

int	change_dir(t_app *app, char *s, int pipe)
{
	int		ret;
	char	*home;
	char	path[PATH_MAX];

	ret = 0;
	if (pipe == 2)
		return (ret);
	create_oldpwd(app, pipe);
	if (!s[0] || !s)
	{
		home = get_env_cd(app, ft_strdup("$HOME"));
		if (!home)
			ret = 5;
		free(home);
		free(s);
		return (ret);
	}
	set_env(app, "OLDPWD", get_env(app, ft_strdup("$PWD")));
	ret = chdir(s);
	set_env(app, "PWD", ft_strdup(getcwd(path, PATH_MAX)));
	free(s);
	return (ret);
}

int	get_old_dir(t_app *app, int pipe)
{
	int		ret;
	char	*s;

	ret = 0;
	s = get_env(app, ft_strdup("$OLDPWD"));
	if (!s[0])
	{
		ft_putstr_fd("Minishell: cd: OLDPWD not set\n", 2);
		if (s)
			free(s);
		g_status = 1;
		app->last_exit = 1;
		return (ret);
	}
	if (pipe == 2)
		return (ret);
	set_env(app, "OLDPWD", get_env(app, ft_strdup("$PWD")));
	set_env(app, "PWD", ft_strdup(s));
	ret = chdir(s);
	if (ret == 0)
		printf("%s\n", s);
	free(s);
	g_status = 0;
	app->last_exit = 0;
	return (ret);
}

int	go_in_dir(t_app *app, char *s, int pipe)
{
	int		err;
	char	*dir;

	err = 0;
	dir = ft_strdup(s);
	err += path_exists(dir);
	if (err != 0)
	{
		err = path_with_cdpath(app, dir);
		if (err == 0)
			dir = (ft_strjoin_properly(get_env(app,
							ft_strdup("$CDPATH")), ft_strdup(s)));
	}
	if (err == 0 && pipe == 0)
		err += change_dir(app, dir, pipe);
	else
		free(dir);
	return (err);
}

void	cd(t_cmd *cmd, t_app *app, int pipe)
{
	int		err;
	char	*oldpwd;

	err = 0;
	if (!cmd->args[0])
		err = change_dir(app, get_env(app, ft_strdup("$HOME")), pipe);
	else if (cmd->args[0])
	{
		if (pipe == 0)
		{
			reset_str(&app->pwd, get_env(app, ft_strdup("$PWD")));
			oldpwd = get_env(app, ft_strdup("$OLDPWD"));
			if (oldpwd[0])
				reset_str(&app->oldpwd, oldpwd);
			else
				free(oldpwd);
		}
		err = rigth_path(app, cmd->args[0], pipe);
	}
	print_err_cd(app, cmd->args[0], err, pipe);
}
