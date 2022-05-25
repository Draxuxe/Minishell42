/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:59:36 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:16 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*str;
	char	*need;
	size_t	i;
	size_t	j;

	str = (char *) haystack;
	need = (char *) needle;
	i = 0;
	j = 0;
	if (ft_strlen(need))
	{
		while (str[i] && i < len)
		{
			while (str[i + j] && need[j] && str[i + j] == need[j])
				j++;
			if (j == ft_strlen(needle) && i + j > len)
				return (NULL);
			else if (j == ft_strlen(needle))
				return (&str[i]);
			j = 0;
			i++;
		}
		return (0);
	}
	return (str);
}
