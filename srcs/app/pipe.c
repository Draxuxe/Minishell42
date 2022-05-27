/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 11:24:55 by aleferra          #+#    #+#             */
/*   Updated: 2022/05/27 15:38:05 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_close_files_up_to(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->pipe[0] > 2)
			close (cmd->pipe[0]);
		if (cmd->pipe[1] > 2)
			close (cmd->pipe[1]);
		if (cmd->input_fd > 2)
			close (cmd->input_fd);
		if (cmd->output_fd > 2)
			close (cmd->output_fd);
		cmd = cmd->pre;
	}
}

static void	wait_for_cmds(t_app **app, t_cmd **cmd)
{
	int		status;
	t_cmd	*tmp;

	status = EXIT_SUCCESS;
	tmp = *cmd;
	while (tmp)
	{
		if (tmp->input_fd < 0)
			g_status = 1;
		else if (is_builtin(tmp->name))
			g_status = (*app)->last_exit;
		else
		{
			waitpid(tmp->pid, &status, 0);
			g_status = WEXITSTATUS (status);
			if (status == 3)
				g_status = 131;
			else if (status == 2)
				g_status = 130;
		}
		tmp = tmp->next;
	}
}

void	pre_exec(t_cmd **cmd)
{
	t_cmd	*tmp;
	int		saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	tmp = *cmd;
	while (tmp)
	{
		if (pipe(tmp->pipe) == -1)
			printf("Broken Pipe\n");
		tmp = tmp->next;
	}
	dup2 (saved_stdin, STDERR_FILENO);
	close (saved_stdin);
}

void	ft_pipe(t_cmd *tmp, t_app **app, int pipe_nb)
{
	char	**env;
	char	*built;

	if (is_builtin(tmp->name) && tmp->input_fd > 0)
		dispatch(app, tmp, pipe_nb);
	else if (tmp->input_fd > 0)
	{
		tmp->pid = fork();
		init_termios(*app, 1);
		catch_pipe_signal();
		if (tmp->pid == 0)
		{
			expand_fd(tmp);
			cmd_close_files_up_to(tmp);
			env = ft_tab_env((*app)->env);
			built = get_native_path(app, tmp->name);
			if (check_cmd(*app, tmp))
				exit(127);
			execve(built, tmp->full, env);
			exit(g_status);
		}
	}
}

void	ft_have_pipe(t_app **app, t_cmd **command, char *line)
{
	int			count;
	t_cmd		*tmp;
	t_cmd		*last;
	int			pipe_nb;

	count = -1;
	tmp = *command;
	pipe_nb = 2;
	if (!(*command)->next)
		pipe_nb = 0;
	pre_exec(command);
	while (tmp)
	{
		ft_pipe(tmp, app, pipe_nb);
		last = tmp;
		tmp = tmp->next;
	}
	cmd_close_files_up_to(last);
	wait_for_cmds(app, command);
	free_end(line, *command);
}
