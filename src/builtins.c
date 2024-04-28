/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:33:10 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/28 00:39:31 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_command command, t_minishell mini)
{
	
	if (command.args[2])
		return (write(2, "minishell: cd: too many arguments\n", 35), 1);
	if(chdir("src/") == 0)
		return (0);
	else
		perror("minishell: cd");
	(void)mini;
	return (0);
	// changer pwd et old getcwd(buffer, 2048); printf("%s\n", buffer);
}

void	ft_pwd()
{
	char	buffer[2048];

	getcwd(buffer, 2048);
	printf("%s\n", buffer);
}

void	ft_envp(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
}

int	is_echon(char *s)
{
	int	i;

	i = 1;
	if (!s)
		return (0);
	if (s[0] == '-')
	{
		while (s[i] == 'n')
			i++;
		if (!s[i])
			return (1);
	}
	return (0);
}

void	ft_echo(t_command command)
{
	int	i;
	int	n;

	i = 1;
	while (is_echon(command.args[i]))
		i++;
	n = i == 1;
	while (command.args[i])
	{
		printf("%s", command.args[i]);
		i++;
	}
	if (n)
		printf("\n");
}

void	find_bultins(t_minishell mini, char **envp, t_command command)
{
	if (ft_strcmp(command.cmd, "cd") == 0)
		ft_cd(command, mini);
	else if (ft_strcmp(command.cmd, "echo") == 0)
		ft_echo(command);
	else if (ft_strcmp(command.cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(command.cmd, "env") == 0)
		ft_envp(envp);
	exit(0);
}

void	to_dup2(t_command command, int pipefd[2], int new_pipe[2])
{
	if (command.infile != -2)
		dup2(command.infile, STDIN_FILENO);
	else
		dup2(pipefd[0], STDIN_FILENO);
	if (command.outfile != -2)
		dup2(command.outfile, STDOUT_FILENO);
	else
		dup2(new_pipe[1], STDOUT_FILENO);
}

int	builtin_continue(t_minishell mini, t_command command, int pipefd[2], char **envp)
{
	pid_t	pid;
	int	new_pipe[2];

	close(pipefd[1]);
	if (pipe(new_pipe) == -1)
		return (close(pipefd[0]), 1);
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(new_pipe[0]);
		close(new_pipe[1]);
		perror("minishell : fork:");
		return (0);
	}
	else if (pid == 0)
		find_bultins(mini, envp, command);
	pipefd[0] = new_pipe[0];
	pipefd[1] = new_pipe[1];
	return (0);
}

int	builtin_null(t_command command)
{
	if (ft_strcmp(command.cmd, "export") == 0)
		return (0);
	else if (ft_strcmp(command.cmd, "exit") == 0)
		return (0);
	else if (ft_strcmp(command.cmd, "unset") == 0)
		return (0);
	return (1);
}

int	not_bultins(t_command command)
{
	if (ft_strcmp(command.cmd, "cd") == 0)
		return (0);
	else if (ft_strcmp(command.cmd, "echo") == 0)
		return (0);
	else if (ft_strcmp(command.cmd, "pwd") == 0)
		return (0);
	else if (ft_strcmp(command.cmd, "env") == 0)
		return (0);
	return (1);
}

void	error_pid(int pipefd[2], int new_pipe[2])
{
	close(pipefd[0]);
	close(new_pipe[0]);
	close(new_pipe[1]);
	perror("minishell : fork:");
}

int	builtin(t_minishell mini, t_command command, char **envp)
{
	if (builtin_null(command) == 0)
		return (0);
	if (not_bultins(command))
		return (1);
	find_bultins(mini, envp, command);
	return (0);
}

int	one_builtin(t_minishell mini, t_command command, char **envp)
{
	if (ft_strcmp(command.cmd, "echo") == 0)
		return (ft_echo(command), 0);
	else if (ft_strcmp(command.cmd, "cd") == 0)
		return (ft_cd(command, mini), 0);
	else if (ft_strcmp(command.cmd, "pwd") == 0)
		return (ft_pwd(), 0);
	else if (ft_strcmp(command.cmd, "env") == 0)
		return (ft_envp(envp), 0);
	else if (ft_strcmp(command.cmd, "exit") == 0)
		return (ft_exit(), 0);
	return (1);
}