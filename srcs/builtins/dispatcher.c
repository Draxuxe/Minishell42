/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleferra <aleferra@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:53:38 by aleferra          #+#    #+#             */
/*   Updated: 2022/05/24 17:28:59 by aleferra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	save_fds(int fd[3])
{
	fd[0] = dup(0);
	fd[1] = dup(1);
	fd[2] = dup(2);
}

static void	restore_fds(int fd[3])
{
	dup2 (fd[0], 0);
	dup2 (fd[1], 1);
	dup2 (fd[2], 2);
	close (fd[0]);
	close (fd[1]);
	close (fd[2]);
}

void	dispatch(t_app **app, t_cmd *cmd, int pipe)
{
	int	fd[3];

	save_fds(fd);
	expand_fd(cmd);
	if (!cmd->name || check_cmd(*app, cmd))
		return ;
	if (ft_strcmp_sensitive(cmd->name, "echo"))
		ft_echo(*app, cmd);
	else if (ft_strcmp_sensitive(cmd->name, "env"))
		our_env(cmd, *app);
	else if (ft_strcmp_sensitive(cmd->name, "export"))
		export(cmd, app, pipe);
	else if (ft_strcmp_sensitive(cmd->name, "pwd"))
		pwd(*app);
	else if (ft_strcmp_sensitive(cmd->name, "exit"))
		our_exit(*app, cmd, pipe);
	else if (ft_strcmp_sensitive(cmd->name, "unset"))
		unset(cmd, app, pipe);
	else if (ft_strcmp_sensitive(cmd->name, "cd"))
		cd(cmd, *app, pipe);
	restore_fds(fd);
}
