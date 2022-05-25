/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:48:27 by aleferra          #+#    #+#             */
/*   Updated: 2022/05/13 15:09:53 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

# include <termios.h>
# include <stdlib.h>

typedef int	t_bool;

# define FALSE 0
# define TRUE 1

# define CMD 21
# define ARG 22

typedef struct s_cmd {
	char			*name;
	char			*name_nu;
	char			**full;
	char			**args;
	char			**args_nu;
	int				output_fd;
	int				input_fd;
	int				pipe[2];
	pid_t			pid;
	t_token			next_t;
	struct s_cmd	*next;
	struct s_cmd	*pre;
}		t_cmd;

typedef struct s_env {
	char			*key;
	char			*value;
	struct s_env	*next;
}		t_env;

typedef struct s_app {
	int				last_exit;
	int				cmd_exit;
	int				err;
	char			*oldpwd;
	char			*pwd;
	struct termios	termios_before;
	struct termios	termios_p;
	t_bool			running;
	t_env			*env;
	t_cmd			*cmd;
}		t_app;

typedef struct s_chain {
	int					index;
	t_token				token;
	struct s_chain		*next;
	struct s_chain		*prev;
}		t_chain;

#endif