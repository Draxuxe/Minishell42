/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:45:11 by aleferra          #+#    #+#             */
/*   Updated: 2022/05/27 15:34:09 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	remove_plus(t_env **env, char *str)
{
	char	*dest;

	dest = ft_strjoin_properly(ft_strtrim(ft_substr
				(str, 0, ft_strchr_bis(str, '=')),
				"+"), ft_strdup(&str[ft_strchr_bis(str, '=')]));
	ft_add_back_env(env, ft_add_new_env(dest));
	if (dest)
		free(dest);
	return (2);
}

void	ft_add_export(t_app *app, t_env **env, char *str, int pipe)
{
	int		i;
	int		err;

	i = 0;
	err = 0;
	if (ft_isalpha(str[0]) || str[0] == '_')
	{
		while (++i < ft_strchr_bis(str, '='))
		{
			if (!(ft_isalpha(str[i]) || str[i] == '_' || ft_isdigit(str[i])))
			{
				err = 1;
				if (str[i] == '+' && str[i + 1] == '=')
					err = remove_plus(env, str);
				break ;
			}
		}
		if (pipe == 0 && err == 0)
			ft_add_back_env(env, ft_add_new_env(str));
		else if (err == 1)
			print_export_err(app, str);
	}
	else
		print_export_err(app, str);
}

void	ft_concat(char *str, t_env *tmp)
{
	tmp->value = ft_strjoin_properly(tmp->value,
			ft_strdup(&str[ft_strchr_bis(str, '=') + 1]));
}

t_bool	is_a_plus(char *tempo, t_env *tmp)
{
	char	*trimed;

	trimed = ft_strtrim(ft_strdup(tempo), "+");
	if (ft_strchr(tempo, '+') == (int)ft_strlen(tmp->key)
		&& ft_strcmp(trimed, tmp->key))
	{
		free (trimed);
		return (TRUE);
	}
	free (trimed);
	return (FALSE);
}

void	print_export_err(t_app *app, char *str)
{
	ft_putstr_fd("Minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_status = 1;
	app->last_exit = 1;
}
