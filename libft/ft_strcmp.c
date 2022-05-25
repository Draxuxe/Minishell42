/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleferra <aleferra@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:23:01 by rblondia          #+#    #+#             */
/*   Updated: 2022/04/12 13:56:09 by aleferra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcomp_valid(char *s1, char *s2)
{
	int	index;

	index = -1;
	while (s1[++index])
	{
		if (s1[index] != s2[index])
			return (s1[index] - s2[index]);
	}
	return (s1[index] - s2[index]);
}

int	ft_strcmp_sensitive(const char *a, const char *b)
{
	int	i;

	if (!a || !b || ft_strlen(a) != ft_strlen(b))
		return (0);
	i = -1;
	while (a[++i])
	{
		if (a[i] != b[i])
			return (0);
	}
	return (1);
}

int	ft_strcmp(const char *a, const char *b)
{
	int	i;

	if (!a || !b || ft_strlen(a) != ft_strlen(b))
		return (0);
	i = -1;
	while (a[++i])
	{
		if (ft_tolower(a[i]) != ft_tolower(b[i]))
			return (0);
	}
	return (1);
}
