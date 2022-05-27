/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 09:25:27 by aleferra          #+#    #+#             */
/*   Updated: 2022/05/27 15:01:18 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*ft_last_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (env)
	{
		if (ft_strcomp_valid(env->key, tmp->key) > 0)
			tmp = env;
		env = env->next;
	}
	return (tmp);
}

void	print_export(t_env *aff)
{
	if (aff->value)
		printf("declare -x %s=\"%s\"\n", aff->key, aff->value);
	else
		printf("declare -x %s\n", aff->key);
}

void	ft_export(t_env *env)
{
	int		i;
	t_env	*aff;
	t_env	*move;
	t_env	*comp;

	aff = NULL;
	comp = NULL;
	i = -1;
	while (aff != ft_last_env(env))
	{
		move = env;
		comp = ft_last_env(env);
		while (move)
		{
			if ((!aff && ft_strcomp_valid(comp->key, move->key) > 0)
				|| (aff && ft_strcomp_valid(comp->key, move->key) > 0
					&& ft_strcomp_valid(aff->key, move->key) < 0))
				comp = move;
			move = move->next;
		}
		aff = comp;
		print_export(aff);
	}
}

void	add_export(t_app *app, char *str, t_env **env, int pipe)
{
	int		mode;
	char	*tempo;
	t_env	*tmp;

	mode = 0;
	tmp = *env;
	tempo = ft_substr(str, 0, ft_strchr_bis(str, '='));
	while (tmp)
	{
		if (ft_strcomp_valid(tmp->key, tempo) == 0 || is_a_plus(tempo, tmp))
		{
			mode = 1;
			if (pipe == 0)
				change_the_env(str, tempo, tmp);
		}
		tmp = tmp->next;
	}
	free(tempo);
	if (mode == 0)
		ft_add_export(app, env, str, pipe);
}

void	export(t_cmd *cmd, t_app **app, int pipe)
{
	int	i;

	i = -1;
	g_status = 0;
	(*app)->last_exit = 0;
	if (cmd->args[0] && !is_all_env(cmd))
	{
		while (cmd->args[++i])
		{
			if (!cmd->args[i][0] && cmd->args_nu[i][0] == '$')
				continue ;
			if (!cmd->args[i][0] || (!ft_strchr(cmd->args[i], '=')
				&& cmd->args_nu[i][0] == '$'))
				print_export_err(*app, cmd->args[i]);
			else if (ft_strchr(cmd->args[i], '='))
				add_export(*app, cmd->args[i], &(*app)->env, pipe);
			else
				add_name_env(*app, cmd->args[i], &(*app)->env, pipe);
		}
	}
	else
		ft_export((*app)->env);
}
