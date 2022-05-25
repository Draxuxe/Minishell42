/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleferra <aleferra@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:20:19 by aleferra          #+#    #+#             */
/*   Updated: 2022/04/22 15:54:12 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

typedef enum s_token {
	AMPERSAND,
	AND,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	QUOTE,
	DQUOTE,
	SPACE,
	LITERAL,
	CMD,
	ARG,
	APPEND,
	HERED,
	PIPE_IN,
	DPIPE_IN,
	PIPE_OUT,
	DPIPE_OUT,
	NONE,
}	t_token;

#endif