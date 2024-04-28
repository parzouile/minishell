/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 01:53:28 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/28 02:12:56 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_end(t_command cmd, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		free(envp[i]);
	free(envp);
	free(cmd.args);
	// if (cmd.infile)
	// 	close(cmd.infile);
	// if (cmd.outfile && cmd.outfile != 1)
	// 	close(cmd.outfile);
}

void	ft_exec(t_minishell mini, t_command command, char **envp, int pipefd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return ;// error
	else if (pid == 0)
	{
        dup2(0, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		if (builtin(mini, command, envp) == 1) // pas sur p-e modifie  envp ???
		{
			if (command.cmd[0] != '/' && command.cmd[0] != '.')
				command.cmd = find_bin(command.cmd, envp); // free this later
			execve(command.cmd, command.args, envp);
			error_msg("minishell: command not found\n");	
		}
		exit(0);
	}
}

void	first_command(t_minishell mini, int pipefd[2])
{
	pid_t	pid;
    t_command	command;
	char		**envp;

	envp = tenv_to_arr(mini->env); // a double free
	if (!envp)
		return ;
	command.args = take_args(&mini->cmd_line, &command);
    mini->cmd_line = mini->cmd_line->next;
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		ft_error("Fork");
	}
	else if (pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
        command.cmd = find_bin(command.cmd, envp);
		if (execve(command.cmd, command.args, envp) == -1)
		    perror("Execution"), exit(0);
	}
	wait(&pid);
}

void	ft_exec3(t_minishell mini, t_command command, char **envp, int pipefd[2])
{
	pid_t	pid;

	close(pipefd[1]);
	pid = fork();
	if (pid == -1)
		return ;// error
	else if (pid == 0)
	{
        int fd = open("test", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		dup2(pipefd[0], STDIN_FILENO);
		if (builtin(mini, command, envp) == 1) // pas sur p-e modifie  envp ???
		{
			if (command.cmd[0] != '/' && command.cmd[0] != '.')
				command.cmd = find_bin(command.cmd, envp); // free this later
			execve(command.cmd, command.args, envp);
			error_msg("minishell: command not found\n");	
		}
		exit(0);
	}
	close(pipefd[0]);
}

void	last_command(t_minishell mini, int pipefd[2])
{
	t_command	command;
	char		**envp;
    pid_t	pid;
	int		fd;

	envp = tenv_to_arr(mini->env); // a double free
	if (!envp)
		return ;
	command.args = take_args(&mini->cmd_line, &command);
    
	close(pipefd[1]);
	fd = 1;
	pid = fork();
	if (pid == -1)
		(close(pipefd[0]), ft_error("fork"));
	else if (pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
        command.cmd = find_bin(command.cmd, envp);
		if (execve(command.cmd, command.args, envp) == -1)
		    perror("Execution"), exit(0);
	}
	wait(&pid);
	close(pipefd[0]);
}