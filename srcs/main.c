/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:36:48 by aleferra          #+#    #+#             */
/*   Updated: 2022/05/12 11:23:57 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_app	app;
	int		exit_status;

	(void) argv;
	if (argc != 1)
		return (1);
	app = ft_init_app(env);
	init_termios(&app, 0);
	exit_status = start_app(&app);
	init_termios(&app, 1);
	free_app(&app);
	return (exit_status);
}
