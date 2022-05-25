/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 11:01:27 by lfilloux          #+#    #+#             */
/*   Updated: 2022/05/24 16:02:39 by aleferra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_perm_err(char *name, int err)
{
	if (err == 0)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": permission denied\n", 2);
		g_status = 126;
	}
	else if (err == 1)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": is a directory\n", 2);
		g_status = 127;
	}
	else if (err == 2)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": command not found\n", 2);
		g_status = 127;
	}
}

int	has_permission(t_app *app, char *test)
{
	struct stat	statbuf;

	if (!lstat(test, &statbuf))
	{
		if (statbuf.st_mode & S_IFREG)
		{
			if (statbuf.st_mode & S_IXUSR)
				return (TRUE);
			else
			{
				app->cmd_exit = 126;
				print_perm_err(test, 0);
				return (FALSE);
			}
		}
		app->cmd_exit = 1;
		print_perm_err(test, 1);
		return (FALSE);
	}
	if (access(test, F_OK | X_OK) == FALSE)
		return (TRUE);
	return (TRUE);
}

int	check_cmd(t_app *app, t_cmd *cmd)
{
	char	*test;

	if (cmd->name_nu[0] == '$' && !cmd->name[0])
		return (0);
	test = get_native_path(&app, cmd->name);
	if ((!test && !is_builtin(cmd->name)) || !cmd->name[0]
		|| ft_strcmp(cmd->name, ".."))
	{
		g_status = 127;
		print_perm_err(cmd->name, 2);
		free(test);
		return (127);
	}
	if (!has_permission(app, test))
	{
		free(test);
		return (127);
	}
	free(test);
	return (0);
}
