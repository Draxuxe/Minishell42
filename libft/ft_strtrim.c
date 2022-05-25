/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:31:33 by rblondia          #+#    #+#             */
/*   Updated: 2022/04/07 13:44:00 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	contains(char c, char const *set)
{
	int	i;

	if (!c || !set)
		return (0);
	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	get_start(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i] && contains(s1[i], set))
		i++;
	return (i);
}

int	get_end(char const *s1, char const *set)
{
	int	i;

	i = ft_strlen(s1);
	while (contains(s1[i - 1], set))
		i--;
	return (i);
}

char	*ft_strtrim(char *s1, char const *set)
{
	char	*new;
	int		start;
	int		end;

	if (!s1)
		return (NULL);
	start = get_start(s1, set);
	end = get_end(s1, set);
	if (end < start)
	{
		free(s1);
		return (ft_strdup(""));
	}
	new = ft_substr(s1, start, end - start);
	if (!new)
		return (NULL);
	free(s1);
	return (new);
}
