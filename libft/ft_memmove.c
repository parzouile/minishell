/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:54:28 by aschmitt          #+#    #+#             */
/*   Updated: 2023/11/11 14:03:25 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	i = -1;
	d = dest;
	s = src;
	if (n == 0)
		return (dest);
	if (d < s)
	{
		while (++i < n)
			d[i] = s[i];
	}
	else if (d > s)
	{
		i = n - 1;
		while (i > 0)
		{
			d[i] = s[i];
			i --;
		}
		d[0] = s[0];
	}
	return (dest);
}
