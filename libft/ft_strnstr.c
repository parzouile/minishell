/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:03:31 by aschmitt          #+#    #+#             */
/*   Updated: 2023/11/06 15:03:42 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	size_t	i;
	size_t	a;
	size_t	b;

	i = 0;
	if (ft_strlen(little) == 0)
		return ((char *)big);
	while (big[i] && i < len)
	{
		a = i;
		b = 0;
		while (big[a] && little[b] && big[a] == little[b] && a < len)
		{
			a ++;
			b ++;
		}
		if (!little[b])
			return ((char *)(big + i));
		i ++;
	}
	return (NULL);
}
