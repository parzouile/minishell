/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:11:26 by aschmitt          #+#    #+#             */
/*   Updated: 2024/05/02 18:20:43 by jbanacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	ft_exec(t_minishell mini, t_command command, int pipefd[2])
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (perror("minishell"), end_command(command), 0);
	else if (pid == 0)
	{
		assign_sig_handler(SIG_FORK);
		dup2(command.outfile, STDOUT_FILENO);
		if (command.infile)
			dup2(command.infile, STDIN_FILENO);
		close(pipefd[0]);
		if (builtin(mini, command, mini->envp) == 1)
		{
			execve(command.cmd, command.args, mini->envp);
			if (command.cmd[0] == '.')
				ft_denied(command, mini);
			error_msg("minishell: command not found\n");
			quit(command, mini, 127);
		}
		quit(command, mini, g_current_status);
	}
	signal(SIGCHLD, child);
	return (end_command(command), pid);
}

pid_t	ft_exec3(t_minishell mini, t_command command)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (perror("minishell"), end_command(command), 0);
	else if (pid == 0)
	{
		assign_sig_handler(SIG_FORK);
		dup2(command.outfile, STDOUT_FILENO);
		dup2(command.infile, STDIN_FILENO);
		if (builtin(mini, command, mini->envp) == 1)
		{
			execve(command.cmd, command.args, mini->envp);
			if (command.cmd[0] == '.')
				ft_denied(command, mini);
			error_msg("minishell: command not found\n");
			quit(command, mini, 127);
		}
		quit(command, mini, g_current_status);
	}
	signal(SIGCHLD, child);
	end_command(command);
	return (pid);
}

void	ft_wait(pid_t pid)
{
	waitpid(pid, &g_current_status, 0);
	if (WIFEXITED(g_current_status))
		g_current_status = WEXITSTATUS(g_current_status);
}

int	exec_one_commande(t_command cmd, t_minishell mini)
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
		execve(cmd.cmd, cmd.args, mini->envp);
		if (cmd.cmd[0] == '.')
			ft_denied(cmd, mini);
		error_msg("minishell: command not found\n");
		quit(cmd, mini, 127);
	}
	signal(SIGCHLD, child);
	ft_wait(pid);
	return (0);
}

void	one_command(t_minishell mini)
{
	t_command	command;

	g_current_status = 0;
	command.exec = 0;
	if (nb_command(mini->cmd_line) == 0)
		return (zero_command(mini));
	command.args = take_args(&mini->cmd_line, &command);
	if (command.args == NULL)
		return ;
	if (redirection(&command, &mini->cmd_line, mini) == 0 || command.exec)
		return (end_command(command));
	mini->fd1 = dup(STDOUT_FILENO);
	mini->fd2 = dup(STDIN_FILENO);
	if (command.infile != -2)
		dup2(command.infile, STDIN_FILENO);
	if (command.outfile != -2)
		dup2(command.outfile, STDOUT_FILENO);
	if (one_builtin(mini, command, mini->envp) == 1)
		exec_one_commande(command, mini);
	end_command(command);
	dup2(mini->fd1, STDOUT_FILENO);
	dup2(mini->fd2, STDIN_FILENO);
	close(mini->fd2);
	close(mini->fd1);
}
