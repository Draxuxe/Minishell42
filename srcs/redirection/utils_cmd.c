/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:56:33 by aleferra          #+#    #+#             */
/*   Updated: 2022/05/10 11:16:38 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	is_valid_fd(t_app *app, char *file)
{
	int	fd;

	fd = dup(ft_atoi(&file[1]));
	if (fd == -1)
		print_fd_err(app, &file[1]);
}

int	count_cmds(char **args)
{
	int		count;
	size_t	i;

	count = 1;
	i = -1;
	while (args[++i])
	{
		if (ft_strcmp_sensitive(args[i], "|"))
			count ++;
	}
	return (count);
}

char	*create_cmd(char **args, int *pos)
{
	char	*dest;

	if (ft_strcmp_sensitive(args[*pos], "|"))
		*pos += 1;
	dest = ft_strdup(args[*pos]);
	*pos += 1;
	while (args[*pos])
	{
		if (ft_strcmp_sensitive(args[*pos], "|"))
			break ;
		dest = ft_strjoin_properly(dest, ft_strdup(" "));
		dest = ft_strjoin_properly(dest, ft_strdup(args[*pos]));
		*pos += 1;
	}
	return (dest);
}

char	**get_cmds(char *str, int err)
{
	char	**args;
	char	**new;
	int		cmds;
	int		index;
	int		pos;

	if (!str || !str[0] || err != TRUE)
		return (NULL);
	index = -1;
	pos = 0;
	args = parse_quotes(str);
	cmds = count_cmds(args);
	new = malloc(sizeof(char *) * (cmds + 1));
	if (!new)
		return (NULL);
	while (++index < cmds)
		new[index] = create_cmd(args, &pos);
	new[index] = NULL;
	free_array(args);
	return (new);
}
