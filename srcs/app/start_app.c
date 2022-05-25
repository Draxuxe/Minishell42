/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_app.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:47:03 by lfilloux          #+#    #+#             */
/*   Updated: 2022/05/18 11:21:22 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_prompt_symbol(void)
{
	if (g_status != 0)
		return (ERROR_PROMPT_SYMBOL);
	return (PROMPT_SYMBOL);
}

void	ft_close(t_app *app)
{
	printf("\b\bMinishell is closing bye!\n");
	init_termios(app, 1);
	exit(EXIT_FAILURE);
}

void	close_minishell(t_app *app)
{
	ft_putstr_fd(CLOSE_PROMPT_SYMBOL, 1);
	init_termios(app, 1);
	app->running = FALSE;
}

void	catch_signal(t_app *app)
{
	app->err = FALSE;
	signal(SIGINT, default_signal_handler);
	signal(SIGQUIT, default_signal_handler);
}

int	start_app(t_app *app)
{
	int			err;
	char		*line;
	t_chain		*tokens;
	t_cmd		*cmd;

	while (app->running == TRUE)
	{
		init_termios(app, 2);
		catch_signal(app);
		line = readline(get_prompt_symbol());
		if (!line)
			ft_close(app);
		tokens = lexer(res_str(&line, ft_strtrim(ft_strdup(line), " \n")));
		err = syntaxer(tokens);
		catch_error(err, tokens);
		cmd = init_cmd(app, get_cmds(line, err));
		add_history(line);
		if (!line[0] || err != TRUE || app->err == TRUE)
		{
			free_end(line, cmd);
			continue ;
		}
		ft_have_pipe(&app, &cmd, line);
	}
	return (g_status);
}
