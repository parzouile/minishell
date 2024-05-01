/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:00:13 by aschmitt          #+#    #+#             */
/*   Updated: 2024/05/01 11:55:51 by jbanacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nb_command(t_token line)
{
	int	n;

	n = 0;
	while (line != NULL)
	{
		if (line->type == 1)
			n++;
		line = line->next;
	}
	return (n);
}

int	exec_one_commande(t_command cmd, char **envp)
{
	pid_t	pid;

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
		execve(cmd.cmd, cmd.args, envp);
		perror("minishell");
		// error_msg("minishell: command not found\n");
		exit(0);
	}
	wait(&pid);
	return (0);
}

void	one_command(t_minishell mini)
{
	t_command	command;
	int			sauvegarde_stdout;
	int			sauvegarde_stdin;

	sauvegarde_stdout = dup(STDOUT_FILENO);
	sauvegarde_stdin = dup(STDIN_FILENO);
	command.args = take_args(&mini->cmd_line, &command);
	if (command.args == NULL)
		return ;
	if (redirection(&command, &mini->cmd_line) == 0)
		return ;// fermer fd et free
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

void	wait_child(pid_t *g_lst_pid)
{
	int	i;

	i = -1;
	while (g_lst_pid[++i])
		wait(&g_lst_pid[i]);
	free(g_lst_pid);
}

void	start_exe(t_minishell mini)
{
	int		pipefd[2];
	pid_t	*g_lst_pid;
	int		i;

	mini->envp = tenv_to_arr(mini->env);
	if (!mini->envp)
		return ;
	if (nb_command(mini->cmd_line) == 1)
		one_command(mini);
	else
	{
		g_lst_pid = ft_calloc(sizeof(pid_t), nb_command(mini->cmd_line) + 1);
		if (!g_lst_pid)
			return (free_tab(mini->envp));
		i = -1;
		if (pipe(pipefd) == -1)
			return (free_tab(mini->envp));
		g_lst_pid[++i] = first_command(mini, pipefd);
		while (nb_command(mini->cmd_line) >= 2)
			g_lst_pid[++i] = mid_command(mini, pipefd);
		g_lst_pid[++i] = last_command(mini, pipefd);
		wait_child(g_lst_pid);
	}
	free_tab(mini->envp);
}
