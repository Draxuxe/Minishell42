/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleferra <aleferra@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:23:01 by rblondia          #+#    #+#             */
/*   Updated: 2022/05/09 17:25:12 by aleferra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr_neg(const char *s, int c)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == c)
			return (i);
	}
	return (-1);
}

int	ft_strchr(const char *s, int c)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == c)
			return (i);
	}
	return (0);
}

int	ft_strchr_bis(const char *s, int c)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == c)
			return (i);
	}
	return (i);
}

int	ft_strcchr(const char *s, char *sep)
{
	int	i;
	int	j;

	i = -1;
	while (s[++i])
	{
		j = -1;
		while (sep[++j])
		{
			if (s[i] == sep[j])
				return (i);
		}
	}
	return (i);
}
