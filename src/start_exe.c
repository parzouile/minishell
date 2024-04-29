/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:32:27 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/29 22:41:40 by aschmitt         ###   ########.fr       */
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

int	nb_args(t_token line)
{
	int	i;

	i = 0;
	while ((line->type == 2 || line->type == 1))
	{
		i++;
		if (line->next == NULL)
			break;
		line = line->next;
	}
	return (i);
}

char	**take_args(t_token *line, t_command *command)
{
	char	**result;
	int		i;
	int		j;

	(*command).cmd = (*line)->str;
	i = nb_args(*line);
	result = (char **)malloc((i + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	j = -1;
	while (++j < i)
	{
		result[j] = (*line)->str;
		if ((*line)->next)
			(*line) = (*line)->next;
	}
	result[i] = NULL;
	return (result);
}

void	end_command(t_command cmd)
{
	int	i;

	i = -1;
	free(cmd.args);
	if (cmd.outfile != -2 && cmd.outfile != 1)
		close(cmd.outfile);
	if (cmd.infile != -2)
		close(cmd.infile);
}

void	open_file(t_command *cmd, t_token *line)
{
	if ((*line) && (*line)->type == 3)
	{
		if (cmd->infile != -2)
			close(cmd->infile);
		cmd->infile = open((*line)->str, O_RDONLY, 0644);
	}
	else if ((*line) && (*line)->type == 4)
	{
		if (cmd->infile != -2)
			close(cmd->infile);
		cmd->infile = get_here_doc((*line)->str);
	}
	else if ((*line) && (*line)->type == 5)
	{
		if (cmd->outfile != -2)
			close(cmd->outfile);
		cmd->outfile = open((*line)->str,  O_WRONLY | O_CREAT | O_TRUNC, 420);
	}
		
	else if ((*line) && (*line)->type == 6)
	{
		if (cmd->outfile != -2)
			close(cmd->outfile);
		cmd->outfile = open((*line)->str,  O_WRONLY | O_CREAT | O_APPEND, 420);
	}
}

int	redirection(t_command *cmd, t_token *line)
{
    cmd->infile = -2;
	cmd->outfile = -2;
	while ((*line) && ((*line)->type == 3 || (*line)->type == 4 || (*line)->type == 5 || (*line)->type == 6))
	{
		open_file(cmd, line);
		if (cmd->infile == -1)
		{
			if (cmd->outfile)
				close(cmd->outfile);
			error_msg("minishell: Error file\n");
			return (0);
		}
		if (cmd->outfile == -1)
		{
			if (cmd->infile)
				close(cmd->infile);
			error_msg("minishell: Error file\n");
			return (0);
		}
		if ((*line)->next)
			break ;
		(*line) = (*line)->next;
	}
	return (1);
}

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
		error_msg("minishell: command not found\n");
		exit(0);
    }
	wait(&pid);
	return (0);
}

void	one_command(t_minishell mini)
{
	t_command	command;

	command.args = take_args(&mini->cmd_line, &command);
	if (redirection(&command,  &mini->cmd_line) == 0)
		return ; // fermer fd et free
	if (command.infile != -2)
		dup2(command.infile, STDIN_FILENO);
	if (command.outfile != -2)
		dup2(command.outfile, STDOUT_FILENO);
	if (one_builtin(mini, command, mini->envp) == 1)
		exec_one_commande(command, mini->envp);
	end_command(command);
}


void afficherContenuFichier(int fd) {
    char buffer[1024]; // Un tampon de 1024 octets pour stocker les données lues du fichier

	printf("debut lecture--------------\n");
    // Lire du fichier tant qu'il y a des données à lire
    ssize_t bytes_lus;
    while ((bytes_lus = read(fd, buffer, sizeof(buffer))) > 0) {
        // Afficher les données lues
        write(STDOUT_FILENO, buffer, bytes_lus);
    }
    // Vérifier s'il y a eu une erreur lors de la lecture
    if (bytes_lus < 0) {
        perror("Erreur lors de la lecture du fichier");
        exit(EXIT_FAILURE);
    }
}

void	start_exe(t_minishell mini)
{
	int		pipefd[2];
	int			sauvegarde_stdout;
	int			sauvegarde_stdin;
	pid_t 	g_lst_pid[100];
	int		i;

	mini->envp = tenv_to_arr(mini->env);
	if (!mini->envp)
		return ;
	sauvegarde_stdout = dup(STDOUT_FILENO);
	sauvegarde_stdin = dup(STDIN_FILENO);
	if (nb_command(mini->cmd_line) == 1)
		one_command(mini);
	else
	{
		i = -1;
		if (pipe(pipefd) == -1)
			ft_error("Pipe");
		g_lst_pid[++i] = first_command(mini, pipefd);
		while (nb_command(mini->cmd_line) >= 2){
			g_lst_pid[++i] = mid_command(mini, pipefd);
		}
		g_lst_pid[++i] = last_command(mini, pipefd);
		g_lst_pid[++i] = 0;
		i = -1;
		while (g_lst_pid[++i])
			wait(&g_lst_pid[i]);
	}
	free_tab(mini->envp);
	dup2(sauvegarde_stdin, STDIN_FILENO);
	dup2(sauvegarde_stdout, STDOUT_FILENO);
}


