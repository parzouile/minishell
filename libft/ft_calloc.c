/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:04:40 by aschmitt          #+#    #+#             */
/*   Updated: 2023/11/07 14:20:38 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	void	*result;
	size_t	i;
	size_t	size;

	size = -1;
	if (elementSize > 0 && elementCount > size / elementSize)
		return (NULL);
	i = 0;
	size = elementCount * elementSize;
	result = malloc(size);
	if (!result)
		return (NULL);
	while (i < (size))
	{
		((unsigned char *)result)[i] = 0;
		i ++;
	}
	return (result);
}
