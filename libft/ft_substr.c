/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:01:39 by rblondia          #+#    #+#             */
/*   Updated: 2022/04/05 13:38:58 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	int		index;

	index = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		new = malloc(sizeof(char));
		new[0] = '\0';
		return (new);
	}
	new = malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	while (s[start + index] && index < (int) len)
	{
		new[index] = s[start + index];
		index++;
	}
	new[index] = '\0';
	return (new);
}
