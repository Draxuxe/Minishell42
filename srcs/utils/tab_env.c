/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:08:59 by aleferra          #+#    #+#             */
/*   Updated: 2022/05/27 15:31:14 by lfilloux         ###   ########.fr       */
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
	int		i;

	i = -1;
	while (str[++i])
	{
		if (!(ft_isalpha(str[i]) || str[i] == '_'
				|| (ft_isdigit(str[i]) && i > 0)))
		{
			print_export_err(app, str);
			return ;
		}
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

void	change_the_env(char *str, char *tempo, t_env *tmp)
{
	if (is_a_plus(tempo, tmp))
		ft_concat(str, tmp);
	else
		reset_str(&tmp->value, ft_strdup(&str[ft_strchr(str, '=') + 1]));
}
