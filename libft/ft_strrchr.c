/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:40:36 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:16 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t		i;
	int			j;
	char		*str;

	str = (char *)s;
	i = 0;
	j = -1;
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			j = i;
		i++;
	}
	if (c == '\0')
		return (&str[i]);
	if (j == -1)
		return (NULL);
	return (&str[j]);
}
