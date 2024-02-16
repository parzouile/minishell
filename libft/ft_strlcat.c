/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:56:12 by aschmitt          #+#    #+#             */
/*   Updated: 2023/11/06 14:56:29 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	b;

	i = 0;
	b = 0;
	while (dst[i])
		i ++;
	while (src[b] && (i + 1) < (size))
	{
		dst[i] = src[b];
		i ++;
		b ++;
	}
	dst[i] = 0;
	if (i > size)
		return (size + ft_strlen(src));
	while (src[b])
	{
		i ++;
		b ++;
	}
	return (i);
}
