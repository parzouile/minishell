/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:00:13 by aschmitt          #+#    #+#             */
/*   Updated: 2024/05/02 19:20:00 by jbanacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nb_command(t_token line)
{
	int	n;

	n = 0;
	while (line != NULL && line->type != 7)
	{
		if (line->type == 1)
			n++;
		line = line->next;
	}
	return (n);
}

int	nb_pipe(t_token line)
{
	int	n;

	n = 0;
	while (line != NULL)
	{
		if (line->type == 7)
			n++;
		line = line->next;
	}
	return (n + 1);
}

void	wait_child(pid_t *g_lst_pid, int n)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		if (g_lst_pid[i] != -1 && g_lst_pid[i] != 0)
		{
			waitpid(g_lst_pid[i], &g_current_status, 0);
			if (WIFEXITED(g_current_status))
				g_current_status = WEXITSTATUS(g_current_status);
			else if (WIFSIGNALED(g_current_status))
				g_current_status = WTERMSIG(g_current_status) + 128;
		}
	}
	// if (g_lst_pid[n - 1] != 0)
	// 	g_current_status = t;
	signal(SIGCHLD, child);
}

void	ft_freeenv(t_minishell mini)
{
	int	i;

	i = -1;
	if (mini->envp)
	{
		while (mini->envp[++i])
			free(mini->envp[i]);
		free(mini->envp);
	}
	mini->envp = NULL;
	if (mini->lst)
		free(mini->lst);
	mini->lst = NULL;
}

void	start_exe(t_minishell mini)
{
	int		pipefd[2];
	int		i;
	int		n;

	mini->envp = tenv_to_arr(mini->env);
	if (!mini->envp)
		return ;
	if (nb_pipe(mini->cmd_line) == 1)
		return (one_command(mini), ft_freeenv(mini));
	mini->lst = ft_calloc(sizeof(pid_t), (n = nb_pipe(mini->cmd_line)));
	if (!mini->lst)
		return (ft_freeenv(mini));
	i = 0;
	if (pipe(pipefd) == -1)
		return (ft_freeenv(mini));
	mini->lst[i++] = first_command(mini, pipefd);
	while (i + 1 < n)
		mini->lst[i++] = mid_command(mini, pipefd);
	mini->lst[i++] = last_command(mini, pipefd);
	wait_child(mini->lst, n);
	assign_sig_handler(SIG_MAIN);
	ft_freeenv(mini);
}
