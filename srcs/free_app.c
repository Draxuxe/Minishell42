/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_app.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleferra <aleferra@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:13:32 by aleferra          #+#    #+#             */
/*   Updated: 2022/04/28 14:27:09 by aleferra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_app(t_app *app)
{
	t_env	*tmp;

	free(app->oldpwd);
	free(app->pwd);
	while (app->env)
	{
		tmp = app->env;
		free(app->env->key);
		free(app->env->value);
		app->env = app->env->next;
		free(tmp);
	}
}
