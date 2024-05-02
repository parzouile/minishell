/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 23:48:49 by jules             #+#    #+#             */
/*   Updated: 2024/05/02 19:05:15 by jbanacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_msg(char *s)
{
	if (!s)
		return (EXIT_FAILURE);
	(void) write(2, s, ft_strlen(s));
	return (EXIT_FAILURE);
}

void	error_here_doc(char *s)
{
	error_msg("minishell: warning: here-document delimited");
	error_msg("by end-of-file (wanted `");
	error_msg(s);
	error_msg("')\n");
}

void	error_cd(void)
{
	error_msg("minishell: cd: error retrieving current directory: getcwd: \
	cannot access parent directories: No such file or directory");
}
