/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 23:48:49 by jules             #+#    #+#             */
/*   Updated: 2024/05/02 16:07:47 by aschmitt         ###   ########.fr       */
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

void	error_here_doc(char *s)
{
	error_msg("minishell: warning: here-document at line 1 delimited");
	error_msg("by end-of-file (wanted `");
	error_msg(s);
	error_msg("')\n");
}
