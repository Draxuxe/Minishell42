/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   native_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleferra <aleferra@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:13:27 by lfilloux          #+#    #+#             */
/*   Updated: 2022/05/09 15:58:34 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_all_paths(t_app **app)
{
	char	**paths;
	char	*env_path;

	env_path = get_env(*app, ft_strdup("$PATH"));
	if (env_path[0])
		paths = ft_split(env_path, ':');
	else
		paths = NULL;
	free(env_path);
	return (paths);
}

int	native_path_exists(char **paths, char *cmd)
{
	int		i;
	char	*test;

	i = 0;
	if (!paths || !paths[0][0])
		return (-1);
	i = -1;
	while (paths[++i])
	{
		test = ft_strjoin(paths[i], "/");
		test = ft_strjoin_properly(test, ft_strdup(cmd));
		if (!access(test, R_OK | X_OK))
		{
			free(test);
			return (1);
		}
		free(test);
	}
	return (0);
}

char	*get_native_path(t_app **app, char *cmd)
{
	char	*path;
	char	**paths;
	int		i;

	if ((cmd[0] == '.' && cmd[1] == '/') || cmd[0] == '/')
		return (ft_strdup(cmd));
	paths = get_all_paths(app);
	if (native_path_exists(paths, cmd) == 1)
	{
		i = -1;
		while (paths[++i])
		{
			path = ft_strjoin(paths[i], "/");
			path = ft_strjoin_properly(path, ft_strdup(cmd));
			if (!access(path, R_OK | X_OK))
			{
				free_array(paths);
				return (path);
			}
			free(path);
		}
	}
	free_array(paths);
	return (NULL);
}
