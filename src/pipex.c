/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:32:29 by aschmitt          #+#    #+#             */
/*   Updated: 2024/03/26 14:20:44 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_lst_pid[100];

pid_t	first_process(char *cmd, int pipefd[2], char **envp)
{
	int		fd;
	pid_t	pid;

	fd = 0;
	pid = fork();
	if (pid == -1)
	{
		close(fd);
		close(pipefd[0]);
		close(pipefd[1]);
		ft_error("Fork");
	}
	else if (pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		dup2(fd, STDIN_FILENO);
		close(pipefd[0]);
		command(cmd, envp);
	}
	return (pid);
}

pid_t	mid_process(int pipefd[2], char *cmd, char **envp)
{
	pid_t	pid;
	int		new_pipe[2];

	close(pipefd[1]);
	if (pipe(new_pipe) == -1)
		(close(pipefd[0]), ft_error("Pipe"));
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(new_pipe[0]);
		close(new_pipe[1]);
		ft_error("Fork");
	}
	else if (pid == 0)
		processus(new_pipe, pipefd, cmd, envp);
	pipefd[0] = new_pipe[0];
	pipefd[1] = new_pipe[1];
	return (pid);
}

pid_t	last_process(char *cmd, int pipefd[2], char **envp)
{
	pid_t	pid;
	int		fd;

	close(pipefd[1]);
	fd = 1;
	if (fd == -1)
		(close(pipefd[0]), ft_error("Error outfile"));
	pid = fork();
	if (pid == -1)
		(close(pipefd[0]), ft_error("fork"));
	else if (pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		dup2(1, STDOUT_FILENO);
		command(cmd, envp);
		(close(pipefd[0]), ft_error("Execution"));
	}
	close(pipefd[0]);
	return (pid);
}

void	ft_ctrlc(int sig)
{
	int	i;

	(void)sig;
	i = -1;
	while (g_lst_pid[++i] != 0)
	{
		printf("kill = %d\n", i);
		kill(g_lst_pid[i], SIGTERM);
		g_lst_pid[i] = 0;
	}
	if (i != 0)
		return ;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void	ft_pipe(int argc, char **lst_pipe, char **envp)
{
	int	pipefd[2];
	int	i;
	int	j;

	i = -1;
	while (++i < argc - 1)
		g_lst_pid[i] = 0;
	if (pipe(pipefd) == -1)
		ft_error("Pipe");
	i = 0;
	g_lst_pid[i] = first_process(lst_pipe[0], pipefd, envp);
	while (++i < argc - 1)
		g_lst_pid[i] = mid_process(pipefd, lst_pipe[i], envp);
	g_lst_pid[i] = last_process(lst_pipe[i], pipefd, envp);
	g_lst_pid[i + 1] = 0;
	i = -1;
	while (g_lst_pid[++i])
		wait(&g_lst_pid[i]);
	j = -1;
	while (++j < i)
		g_lst_pid[j] = 0;
}
