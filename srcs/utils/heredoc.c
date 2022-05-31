/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:43:35 by aleferra          #+#    #+#             */
/*   Updated: 2022/05/31 14:16:49 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle(char *line, int p_fd[2], int test, t_app *app)
{
	if (line)
		free(line);
	close(p_fd[1]);
	dup2(test, 0);
	if (g_status == -53)
	{
		g_status = 1;
		app->err = TRUE;
	}
}

void	catch_new_signal(int signal)
{
	if (signal == SIGINT)
	{
		g_status = -53;
		close (0);
		printf("\n");
	}
}

char	*find_env(char *str, t_app *app)
{
	int		start;
	int		end;
	char	*res;
	char	*replace;

	while (ft_strchr(str, '$') || str[0] == '$')
	{
		start = ft_strchr(str, '$');
		end = ft_strcchr(&str[ft_strchr(str, '$') + 1], " '$\"\0") + start +1;
		replace = ft_substr(str, start, end - start);
		replace = get_env(app, replace);
		res = ft_strjoin_properly(ft_substr(str, 0, start), replace);
		str = ft_strjoin_properly(res, ft_substr(str, end, ft_strlen(str)));
	}
	return (str);
}
