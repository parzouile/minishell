/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:51:04 by aschmitt          #+#    #+#             */
/*   Updated: 2023/11/14 17:34:40 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	if (*lst == NULL || del == NULL)
		return ;
	if ((*lst)->next != NULL)
		ft_lstclear((&(*lst)->next), del);
	del((*lst)->content);
	free(*lst);
	*lst = NULL;
}
