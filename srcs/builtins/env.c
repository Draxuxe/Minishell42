/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:18:11 by lfilloux          #+#    #+#             */
/*   Updated: 2022/05/24 16:10:22 by aleferra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!tmp->value)
		{
			tmp = tmp->next;
			continue ;
		}
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void	set_env(t_app *app, char *env1, char *new)
{
	t_env	*tmp;

	tmp = app->env;
	while (tmp)
	{
		if (ft_strcmp_sensitive(tmp->key, env1))
		{
			free(tmp->value);
			tmp->value = ft_strdup(new);
			break ;
		}
		tmp = tmp->next;
	}
	free(new);
}

char	*get_env_cd(t_app *app, char *str)
{
	t_env	*tmp;

	tmp = app->env;
	if (ft_strcmp_sensitive(str, "$"))
		return (str);
	else if (ft_strcmp_sensitive(str, "$?"))
		return (ft_itoa(g_status));
	while (tmp)
	{
		if (ft_strcmp_sensitive(tmp->key, &str[1]))
			break ;
		tmp = tmp->next;
	}
	free(str);
	if (!tmp)
		return (NULL);
	if (!tmp->value)
		return (ft_strdup(""));
	return (ft_strdup(tmp->value));
}

char	*get_env(t_app *app, char *str)
{
	t_env	*tmp;

	tmp = app->env;
	if (ft_strcmp_sensitive(str, "$"))
		return (str);
	else if (ft_strcmp_sensitive(str, "$?"))
	{
		reset_str(&str, ft_itoa(g_status));
		return (str);
	}
	while (tmp)
	{
		if (ft_strcmp_sensitive(tmp->key, &str[1]))
			break ;
		tmp = tmp->next;
	}
	free(str);
	if (!tmp || !tmp->value)
		return (ft_strdup(""));
	return (ft_strdup(tmp->value));
}

void	our_env(t_cmd *cmd, t_app *app)
{
	int		i;

	i = -1;
	while (cmd->args[++i])
	{
		if (!cmd->args[i][0] && cmd->args_nu[i][0] == '$')
			continue ;
		else if (cmd->args[i])
		{
			ft_putstr_fd("env: ", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			app->last_exit = 1;
			g_status = 1;
			return ;
		}
		else
			break ;
	}
	if (!cmd->next)
		print_env(app->env);
	g_status = 0;
	app->last_exit = 0;
}
