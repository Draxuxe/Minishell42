/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleferra <aleferra@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:06:38 by lfilloux          #+#    #+#             */
/*   Updated: 2022/05/24 15:39:34 by aleferra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(t_app *app)
{
	char	path[PATH_MAX];

	getcwd(path, PATH_MAX);
	printf("%s\n", path);
	g_status = 0;
	app->last_exit = 0;
}
