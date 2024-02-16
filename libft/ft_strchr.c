/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:59:23 by aschmitt          #+#    #+#             */
/*   Updated: 2023/11/14 14:31:26 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	a;

	a = (unsigned char)c;
	i = 0;
	while (str[i])
	{
		if (str[i] == a)
			return ((char *)str + i);
		i ++;
	}
	if (a == 0)
		return ((char *)str + i);
	return (NULL);
}
