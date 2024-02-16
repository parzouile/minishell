/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:02:57 by aschmitt          #+#    #+#             */
/*   Updated: 2023/11/14 12:02:18 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *p1, const void *p2, size_t size)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	s2 = (unsigned char *)p2;
	s1 = (unsigned char *)p1;
	i = 0;
	if (size == 0)
		return (0);
	while (s1[i] == s2[i] && (i + 1) < size)
		i ++;
	return (s1[i] - s2[i]);
}
