/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:49:54 by aleferra          #+#    #+#             */
/*   Updated: 2022/05/18 15:02:03 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*add_new_cmd(t_app *app, char *str, size_t len, size_t i)
{
	t_cmd	*cmd;
	char	**split;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	split = split_quote(str);
	cmd->name = find_cmd_name(app, split);
	cmd->name_nu = find_cmd_name_nu(app, split);
	cmd->output_fd = find_redir_out(app, split);
	cmd->input_fd = find_redir_in(app, split, cmd->name);
	cmd->args = get_args(app, split);
	cmd->args_nu = get_args_nu(split);
	cmd->full = get_full_name(cmd->name, cmd->args);
	cmd->next_t = is_a_pipe(len, i);
	cmd->next = NULL;
	cmd->pre = NULL;
	free_array(split);
	return (cmd);
}

void	add_back_cmd(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*tmp;

	if (!*cmd)
		*cmd = new;
	else
	{
		tmp = *cmd;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->pre = tmp;
	}
}

t_cmd	*init_cmd(t_app *app, char **str)
{
	t_cmd	*cmd;
	size_t	len;
	size_t	i;

	if (!str || !str[0])
		return (NULL);
	cmd = NULL;
	len = array_length(str);
	i = -1;
	while (str[++i])
		add_back_cmd(&cmd, add_new_cmd(app, str[i], len, i));
	free_array(str);
	return (cmd);
}
