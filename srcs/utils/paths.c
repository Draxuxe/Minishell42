/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:00:39 by lfilloux          #+#    #+#             */
/*   Updated: 2022/05/31 13:34:22 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	path_exists(char *s)
{
	DIR		*dir;

	if (!s)
		return (FALSE);
	dir = opendir(s);
	if (!dir)
		return (1);
	closedir(dir);
	return (0);
}

int	path_with_cdpath(t_app *app, char *s)
{
	int		ret;
	char	*cdpath;

	cdpath = get_env(app, ft_strdup("$CDPATH"));
	if (!cdpath)
		return (-1);
	if (!cdpath[0])
	{
		free(cdpath);
		return (-1);
	}
	cdpath = ft_strjoin_properly(cdpath, ft_strdup(s));
	ret = path_exists(cdpath);
	free(cdpath);
	return (ret);
}

int	rigth_path(t_app *app, char *s, int pipe)
{
	int		err;

	err = 0;
	if (!s[0])
		create_oldpwd(app, pipe);
	else if (ft_strcmp_sensitive(s, "~"))
		err = change_dir(app, get_env(app, ft_strdup("$HOME")), pipe);
	else if (ft_strcmp_sensitive(s, "-"))
		err = get_old_dir(app, pipe);
	else
		err += go_in_dir(app, s, pipe);
	return (err);
}
