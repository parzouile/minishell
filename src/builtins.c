/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:08:54 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/25 14:42:31 by aschmitt         ###   ########.fr       */
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

int	find_bultins(t_minishell mini, char **envp, t_command command)
{
	
	// for (size_t i = 0; command.args[i]; i++)
	// {
	// 	write(1, command.args[i], ft_strlen(command.args[i] + 1));
	// 	printf("args : %s\n", command.args[i]);
	// }
	// printf("jean");
	// fflush(stdout);
	
	if (ft_strcmp(command.cmd, "cd") == 0)
		return (ft_cd(command, mini));
	else if (ft_strcmp(command.cmd, "exit") == 0)
		return (ft_exit(), 0);
	else if (ft_strcmp(command.cmd, "pwd") == 0)
		return (ft_pwd(), 0);
	else if (ft_strcmp(command.cmd, "env") == 0)
		return (ft_envp(envp), 0);
	// else if (ft_strcmp(command.cmd, "export") == 0)
	// 	return (ft_export(command, mini), 0);
	// else if (ft_strcmp(command.cmd, "unset") == 0)
	// 	return (ft_unset(command, mini), 0);
	return (1);
}

int	builtin(t_minishell mini, t_command command, int pipefd[2], char **envp)
{
	pid_t	pid;
	int	new_pipe[2];

	close(pipefd[1]);
	if (pipe(new_pipe) == -1)
		return (close(pipefd[0]), 1);
	pid = fork();
	if (pid == -1)
	{
		if (command.infile != -2)
			close(command.infile);
		if (command.outfile != -2 && command.outfile != 1)
			close(command.outfile);
		close(pipefd[0]);
		close(new_pipe[0]);
		close(new_pipe[1]);
		return (1);
	}
	else if (pid == 0)
	{
		if (command.infile != -2)
			dup2(command.infile, STDIN_FILENO);
		else
			dup2(pipefd[0], STDIN_FILENO);
		if (command.outfile != -2)
			dup2(command.outfile, STDOUT_FILENO);
		else
			dup2(new_pipe[1], STDOUT_FILENO);
		find_bultins(mini, envp, command);
		// close(pipefd[0]);
		// command(cmd, envp);
	}
	pipefd[0] = new_pipe[0];
	pipefd[1] = new_pipe[1];
	return (0);
}

int	one_builtin(t_minishell mini, t_command command, char **envp)
{
	if (ft_strcmp(command.cmd, "cd") == 0)
		return (ft_cd(command, mini));
	else if (ft_strcmp(command.cmd, "exit") == 0)
		return (ft_exit(), 0);
	else if (ft_strcmp(command.cmd, "pwd") == 0)
		return (ft_pwd(), 0);
	else if (ft_strcmp(command.cmd, "env") == 0)
		return (ft_envp(envp), 0);
	return (1);
}
