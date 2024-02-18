/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:01:21 by aschmitt          #+#    #+#             */
/*   Updated: 2024/02/18 19:51:38 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(char *s)
{
	signal(2, ft_exit);
	if (s == NULL ||  check_nl(s) == -1)
		ft_putstr_fd("\n", 1);
	else
		ft_putstr_fd(s, 1);
}
