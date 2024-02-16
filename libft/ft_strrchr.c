/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:59:57 by aschmitt          #+#    #+#             */
/*   Updated: 2023/11/14 17:36:41 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	int		n;
	char	a;

	i = 0;
	n = -1;
	a = (char)c;
	while (str[i])
	{
		if (str[i] == a)
			n = i;
		i ++;
	}
	if (a == 0)
		return ((char *)str + i);
	if (n == -1)
		return (NULL);
	return ((char *)str + n);
}
