/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:00:13 by aschmitt          #+#    #+#             */
/*   Updated: 2024/05/02 12:40:49 by aschmitt         ###   ########.fr       */
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

void	ft_wait(pid_t pid)
{
	waitpid(pid, &g_current_status, 0);
	if (WIFEXITED(g_current_status))
		g_current_status = WEXITSTATUS(g_current_status);
}

int	exec_one_commande(t_command cmd, char **envp)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		if (cmd.infile != -2)
			close(cmd.infile);
		if (cmd.outfile != -2)
			close(cmd.outfile);
		return (1);
	}
	else if (pid == 0)
	{
		assign_sig_handler(SIG_FORK);
		execve(cmd.cmd, cmd.args, envp);
		if (access(cmd.cmd, F_OK) == 0)
			ft_denied(cmd.cmd);
		error_msg("minishell: command not found\n");
		exit(127);
	}
	signal(SIGCHLD, child);
	ft_wait(pid);
	return (0);
}

void	one_command(t_minishell mini)
{
	t_command	command;
	int			sauvegarde_stdout;
	int			sauvegarde_stdin;

	g_current_status = 0;
	command.exec = 0;
	if (nb_command(mini->cmd_line) == 0)
		return (zero_command(mini));
	command.args = take_args(&mini->cmd_line, &command);
	if (command.args == NULL)
		return ;
	if (redirection(&command, &mini->cmd_line, mini) == 0 || command.exec)
		return (end_command(command));// fermer fd et free
	sauvegarde_stdout = dup(STDOUT_FILENO);
	sauvegarde_stdin = dup(STDIN_FILENO);
	if (command.infile != -2)
		dup2(command.infile, STDIN_FILENO);
	if (command.outfile != -2)
		dup2(command.outfile, STDOUT_FILENO);
	if (one_builtin(mini, command, mini->envp) == 1)
		exec_one_commande(command, mini->envp);
	end_command(command);
	dup2(sauvegarde_stdin, STDIN_FILENO);
	dup2(sauvegarde_stdout, STDOUT_FILENO);
	close(sauvegarde_stdout);
	close(sauvegarde_stdin);
}

void	wait_child(pid_t *g_lst_pid, int n)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		if (g_lst_pid[i] != -1)
			waitpid(g_lst_pid[i], &g_current_status, 0);
	}
	if (WIFEXITED(g_current_status))
        g_current_status = WEXITSTATUS(g_current_status);
	signal(SIGCHLD, child);
		//wait(&g_lst_pid[i]);
	free(g_lst_pid);
}

void	ft_freeenv(t_minishell mini)
{
	int	i;

	i = -1;
	while (mini->envp[++i])
		free(mini->envp[i]);
	free(mini->envp);
	mini->envp = NULL;
}

void	start_exe(t_minishell mini)
{
	int		pipefd[2];
	pid_t	*lst;
	int		i;
	int		n;

	mini->envp = tenv_to_arr(mini->env);
	if (!mini->envp)
		return ;
	if (nb_pipe(mini->cmd_line) == 1)
		return (one_command(mini), ft_freeenv(mini));
	lst = ft_calloc(sizeof(pid_t), (n = nb_pipe(mini->cmd_line)));
	if (!lst)
		return (ft_freeenv(mini));
	i = 0;
	if (pipe(pipefd) == -1)
		return (ft_freeenv(mini));
	lst[i++] = first_command(mini, pipefd);
	while (i + 1 < n)
		lst[i++] = mid_command(mini, pipefd);
	lst[i++] = last_command(mini, pipefd);
	wait_child(lst, n);
	assign_sig_handler(SIG_MAIN);
	ft_freeenv(mini);
}
