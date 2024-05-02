/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:24:06 by jbanacze          #+#    #+#             */
/*   Updated: 2024/05/02 15:24:27 by jbanacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_sig_handler(int mod)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (mod == SIG_MAIN)
	{
		sa.sa_handler = sig_main_handle;
		signal(SIGQUIT, SIG_IGN);
	}
	if (mod == SIG_FORK)
	{
		sa.sa_flags = SA_SIGINFO;
		sa.sa_handler = sig_fork_handle;
		sigaction(SIGQUIT, &sa, NULL);
	}
	if (mod == SIG_HEREDOC)
	{
		sa.sa_handler = sig_heredoc_handle;
		signal(SIGQUIT, SIG_IGN);
	}
	sigaction(SIGINT, &sa, NULL);
}

void	child(int sig)
{
	(void)sig;
	if (g_current_status == 2)
	{
		g_current_status = 130;
		write(1, "\n", 1);
	}
	if (g_current_status == 131)
		write(1, "Quit (core dumped)\n", 19);
}
