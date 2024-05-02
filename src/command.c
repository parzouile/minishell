/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 00:59:49 by aschmitt          #+#    #+#             */
/*   Updated: 2024/05/02 14:59:21 by aschmitt         ###   ########.fr       */
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
			if (access(command.cmd, F_OK) == 0)
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
			if (access(command.cmd, F_OK) == 0)
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

void	go_next_pipe(t_minishell mini)
{
	while (mini->cmd_line && mini->cmd_line->type != 7)
	{
		if (!mini->cmd_line->next)
			break ;
		mini->cmd_line = mini->cmd_line->next;
	}
	if (mini->cmd_line && mini->cmd_line->type == 7)
		mini->cmd_line = mini->cmd_line->next;
}

pid_t	first_command(t_minishell mini, int pipefd[2])
{
	t_command	command;

	g_current_status = 0;
	command.exec = 0;
	// printf("first\n");
	// print_token(mini->cmd_line);
	if (nb_command(mini->cmd_line) == 0)
	{
		// printf("first no cmd\n");
		return (zero_command(mini), 0);
	}
	command.args = take_args(&mini->cmd_line, &command);	
	if (command.args == NULL)
		return (go_next_pipe(mini), 0);
	if (redirection(&command, &mini->cmd_line, mini) == 0 || command.exec)
		return (go_next_pipe(mini), end_command(command), 0);
	if (command.outfile == -2)
		command.outfile = pipefd[1];
	else
		close(pipefd[1]);
	while (mini->cmd_line && mini->cmd_line->type != 7)
		mini->cmd_line = mini->cmd_line->next;
	mini->cmd_line = mini->cmd_line->next;
	return (ft_exec(mini, command, pipefd));
}

pid_t	mid_command(t_minishell mini, int pipefd[2])
{
	t_command	command;
	int			newpipe[2];
	pid_t		pid;

	close(pipefd[1]);
	command.exec = 0;
	if (g_current_status == 130)
	{
		close(pipefd[0]);
		return (0);
	}
	if (pipe(newpipe) == -1)
		return (close(pipefd[0]), 1);
	if (nb_command(mini->cmd_line) == 0)
	{
		close(pipefd[0]);
		pipefd[0] = newpipe[0];
		pipefd[1] = newpipe[1];
		return (zero_command(mini), 0);
	}
	
	command.args = take_args(&mini->cmd_line, &command);
	if (command.args == NULL)
		return (go_next_pipe(mini), 0);
	if (redirection(&command, &mini->cmd_line, mini) == 0 || command.exec)
		return (go_next_pipe(mini), end_command(command), 0);
	if (command.infile == -2)
		command.infile = pipefd[0];
	else
		close(pipefd[0]);
	if (command.outfile == -2)
		command.outfile = newpipe[1];
	while (mini->cmd_line && mini->cmd_line->type != 7)
		mini->cmd_line = mini->cmd_line->next;
	mini->cmd_line = mini->cmd_line->next;
	pid = ft_exec3(mini, command);
	pipefd[0] = newpipe[0];
	pipefd[1] = newpipe[1];
	return (pid);
}

pid_t	last_command(t_minishell mini, int pipefd[2])
{
	t_command	cmd;

	close(pipefd[1]);
	// printf("last\n");
	// print_token(mini->cmd_line);
	// printf("last nb command %d\n", nb_command(mini->cmd_line));
	cmd.exec = 0;
	if (g_current_status == 130)
	{
		close(pipefd[0]);
		return (0);
	}
	if (nb_command(mini->cmd_line) == 0)
	{
		close(pipefd[0]);
		return (zero_command(mini), 0);
	}
	cmd.args = take_args(&mini->cmd_line, &cmd);
	if (cmd.args == NULL)
		return (0);
	if (redirection(&cmd, &mini->cmd_line, mini) == 0 || cmd.exec)
		return (end_command(cmd), 0); // fermer fd et free
	if (cmd.infile == -2)
		cmd.infile = pipefd[0];
	else
		close(pipefd[0]);
	if (cmd.outfile == -2)
		cmd.outfile = 1;
	return (ft_exec3(mini, cmd));
}
