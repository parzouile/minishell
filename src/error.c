/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 23:48:49 by jules             #+#    #+#             */
/*   Updated: 2024/04/26 23:58:06 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *s)
{
	perror(s);
	exit(1);
}

int	error_msg(char *s)
{
	if (!s)
		return (EXIT_FAILURE);
	(void) write(2, s, ft_strlen(s));
	return (EXIT_FAILURE);
}
