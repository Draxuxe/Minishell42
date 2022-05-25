/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:09:47 by aleferra          #+#    #+#             */
/*   Updated: 2022/05/16 12:58:23 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_termios(t_app *app, int nb)
{
	if (nb == 0)
	{
		tcgetattr(0, &app->termios_before);
		app->termios_p = app->termios_before;
		app->termios_p.c_lflag &= ~ECHOCTL;
	}
	else if (nb == 1)
		tcsetattr(0, TCSANOW, &app->termios_before);
	else if (nb == 2)
		tcsetattr(0, TCSANOW, &app->termios_p);
}

void	handler_signal(int signal)
{
	(void)signal;
	g_status = 1;
	ft_putstr_fd("\b\b\n\b\b", 0);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	pipe_signal_handler(int signo)
{
	if (signo == SIGINT)
		printf("\n");
	else if (signo == SIGQUIT)
		printf("Quit: %d\n", signo);
}

void	catch_pipe_signal(void)
{
	signal(SIGINT, pipe_signal_handler);
	signal(SIGQUIT, pipe_signal_handler);
}

void	default_signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_status = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line ("", 0);
		rl_redisplay ();
	}
	else if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay ();
	}
}
