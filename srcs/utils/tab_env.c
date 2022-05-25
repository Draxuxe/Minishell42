/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleferra <aleferra@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:08:59 by aleferra          #+#    #+#             */
/*   Updated: 2022/05/24 17:26:06 by aleferra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strlen_env(t_env *env)
{
	int	index;

	index = 0;
	while (env)
	{
		index++;
		env = env->next;
	}
	return (index);
}

char	*ft_double_join(t_env *env)
{
	char	*res;
	char	*tmp;

	if (env->value == NULL)
		res = ft_strdup(env->key);
	else
	{
		tmp = ft_strjoin(env->key, "=");
		res = ft_strjoin(tmp, env->value);
		free(tmp);
	}
	return (res);
}

char	**ft_tab_env(t_env *env)
{
	int		index;
	int		nb_env;
	char	**tab;

	index = -1;
	nb_env = ft_strlen_env(env);
	tab = malloc(sizeof(char *) * (nb_env + 1));
	if (!tab)
		return (NULL);
	while (++index < nb_env)
	{
		tab[index] = ft_double_join(env);
		env = env->next;
	}
	tab[index] = NULL;
	return (tab);
}

void	add_name_env(t_app *app, char *str, t_env **env, int pipe)
{
	char	*exist;

	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		ft_putstr_fd("export: '", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_status = 1;
		return ;
	}
	exist = get_env_cd(app, ft_strjoin("$", str));
	if (exist)
		free(exist);
	else
	{
		if (pipe == 0)
			ft_add_back_env(env, ft_add_new_env(str));
	}
}
