/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startexe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:30:31 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/15 15:26:12 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_pipe(int argc, char **lst_pipe, char **envp)
// {
// 	int		pipefd[2];
// 	int		i;
// 	int		j;
// 	pid_t	g_lst_pid[100];

// 	i = -1;
// 	while (++i < argc - 1)
// 		g_lst_pid[i] = 0;
// 	if (pipe(pipefd) == -1)
// 		ft_error("Pipe");
// 	i = 0;
// 	g_lst_pid[i] = first_process(lst_pipe[0], pipefd, envp);
// 	while (++i < argc - 1)
// 		g_lst_pid[i] = mid_process(pipefd, lst_pipe[i], envp);
// 	g_lst_pid[i] = last_process(lst_pipe[i], pipefd, envp);
// 	g_lst_pid[i + 1] = 0;
// 	i = -1;
// 	while (g_lst_pid[++i])
// 		wait(&g_lst_pid[i]);
// 	j = -1;
// 	while (++j < i)
// 		g_lst_pid[j] = 0;
// }

char	**take_args(t_token line)
{
	char	**result;
	int		i;
	int		j;

	i = 1;
	while (line->next->type == 2)
	{
		i++;
		line = line->next;
	}
	result = (char **)malloc((i + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result[i--] = NULL;
	while (i >= 0)
	{
		result[i--] = line->str;
		line->prev;
	}
	while (line->type == 2)
		line = line->next;
	return (result);
}

void	commande(t_command cmd, int pipefd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		if (cmd.infile != -2)
			close(cmd.infile);
		if (cmd.outfile != -2)
			close(cmd.outfile);
		close(pipefd[0]);
		close(pipefd[1]);
		return ;
	}
	else if (pid == 0)
	{
		// dup2(pipefd[1], STDOUT_FILENO);
		// dup2(fd, STDIN_FILENO);
		// close(pipefd[0]);
		// command(cmd, envp);
	}
	return (pid);
}

void	start_command(t_token line, char **envp, int pipefd[2])
{
	t_command	command;

	command.cmd = line->str;
	line = line->next;
	command.args = NULL;
	command.infile = -2;
	command.outfile = -2;
	if (line && line->type == 2)
		command.args = take_args(line);
	if (line && line->type == 3)
	{
		command.infile = open(line->str, O_RDONLY, 0644);
		if (command.infile == -1)
			return ;
		line = line->next;
	}
	else if (line && line->type == 4)
	{
		command.infile = Here_doc(line->str);
		line = line->next;
	}
	if (line && line->type == 5)
	{
		command.outfile = open(line->str,  O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (command.outfile == -1)
			return ;
		line = line->next;
	}
	else if (line && line->type == 6)
	{
		command.outfile = open(line->str,  O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
		if (command.outfile == -1)
			return ;
		line = line->next;
	}
	
	
}

void	start_exe(t_minishell mini, char **envp)
{
	int	pipefd[2];

	(void)mini;
	(void)envp;
	 if (pipe(pipefd) == -1)
		ft_error("Pipe");
	start_command(mini->cmd_line, envp, pipefd);
}
