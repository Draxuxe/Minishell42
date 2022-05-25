/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:32:45 by aleferra          #+#    #+#             */
/*   Updated: 2022/05/24 11:31:07 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_add_back_env(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (!*env)
		*env = new;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		if (ft_strcmp_sensitive(new->key, "SHLVL"))
			reset_str(&(new->value), ft_itoa(ft_atoi(new->value) + 1));
		tmp->next = new;
	}
}

t_env	*ft_add_new_env(char *str)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	if (ft_strchr(str, '=') > 0)
	{
		env->key = ft_substr(str, 0, ft_strchr(str, '='));
		env->value = ft_strdup(&str[ft_strchr(str, '=') + 1]);
	}
	else
	{
		env->key = ft_strdup(str);
		env->value = NULL;
	}
	env->next = NULL;
	return (env);
}

void	init_our_env(t_env **env)
{
	char	*pwd;
	char	*shlvl;
	char	*last;
	char	path[PATH_MAX];

	pwd = ft_strjoin("PWD=", getcwd(path, PATH_MAX));
	shlvl = ft_strdup("SHLVL=1");
	last = ft_strdup("_=/usr/bin/env");
	ft_add_back_env(env, ft_add_new_env(pwd));
	ft_add_back_env(env, ft_add_new_env(shlvl));
	ft_add_back_env(env, ft_add_new_env(last));
	free(pwd);
	free(shlvl);
	free(last);
}

t_env	*ft_init_env(char **env)
{
	t_env	*start_env;
	int		index;

	start_env = NULL;
	if (!env || !env[0])
		init_our_env(&start_env);
	else
	{
		index = -1;
		while (env[++index])
		{
			if (!ft_strncmp("OLDPWD", env[index], 6))
				continue ;
			ft_add_back_env(&start_env, ft_add_new_env(env[index]));
		}
	}
	return (start_env);
}
