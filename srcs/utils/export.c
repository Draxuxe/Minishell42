/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleferra <aleferra@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:45:11 by aleferra          #+#    #+#             */
/*   Updated: 2022/05/24 16:29:26 by aleferra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_add_export(t_env **env, char *str, int pipe)
{
	if (ft_isalpha(str[0]) || str[0] == '_')
	{
		if (pipe == 0)
			ft_add_back_env(env, ft_add_new_env(str));
	}
	else
		print_export_err(NULL, str);
}

void	print_export_err(t_app *app, char *str)
{
	ft_putstr_fd("Minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_status = 1;
	app->last_exit = 1;
}
