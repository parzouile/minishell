/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:54:37 by jbanacze          #+#    #+#             */
/*   Updated: 2024/05/02 12:33:14 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

static void	ctrl_c_action(void)
{
	g_current_status = 130;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	ctrl_s_action(void)
{
	g_current_status = 131;
	error_msg("Quit\n");
}

void	sig_main_handle(int signal)
{
	if (signal == SIGINT)
		ctrl_c_action();
}

void	sig_fork_handle(int signal)
{
	if (signal == SIGINT)
	{
		ctrl_c_action();
	}
		
	if (signal == SIGQUIT)
		ctrl_s_action();
}

void	sig_heredoc_handle(int signal)
{
	if (signal == SIGINT)
	{
		g_current_status = 130;
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

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

// signal(SIGINT, SIG_IGN);
// assign_sig_handler(SIG_FORK)