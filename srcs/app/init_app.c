/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_app.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:30:01 by aleferra          #+#    #+#             */
/*   Updated: 2022/05/24 12:11:03 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_app	ft_init_app(char **env)
{
	t_app	app;

	app.running = TRUE;
	app.last_exit = 0;
	app.err = 0;
	app.cmd_exit = 0;
	app.env = ft_init_env(env);
	app.cmd = NULL;
	app.oldpwd = ft_strdup("");
	app.pwd = ft_strdup("");
	return (app);
}
