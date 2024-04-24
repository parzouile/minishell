/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startexe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:30:31 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/24 10:51:33 by aschmitt         ###   ########.fr       */
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
	while ((line->type == 2  || line->type == 1))
	{
		i++;
		if (line->next == NULL)
			break;
		line = line->next;

	}
	return (i);
}

char	**take_args(t_token *line)
{
	char	**result;
	int		i;
	int		j;

	i = nb_args(*line);
	result = (char **)malloc((i + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	j = -1;
	while (++j < i)
	{
		result[j] = (*line)->str;
		(*line) = (*line)->next;
	}
	result[i] = NULL;
	return (result);
}



int	commande(t_command cmd, int pipefd[2], char **envp)
{
	pid_t	pid;
	int	new_pipe[2];

	close(pipefd[1]);
	if (pipe(new_pipe) == -1)
		return (close(pipefd[0]), 1);
	pid = fork();
	if (pid == -1)
	{
		if (cmd.infile != -2)
			close(cmd.infile);
		if (cmd.outfile != -2)
			close(cmd.outfile);
		close(pipefd[0]);
		close(new_pipe[0]);
		close(new_pipe[1]);
		return (1);
	}
	else if (pid == 0)
	{
		if (cmd.infile != -2)
			dup2(cmd.infile, STDIN_FILENO);
		else
			dup2(pipefd[0], STDIN_FILENO);
		if (cmd.outfile != -2)
			dup2(cmd.outfile, STDOUT_FILENO);
		else
			dup2(new_pipe[1], STDOUT_FILENO);
		execve(cmd.cmd, cmd.args, envp);
		// close(pipefd[0]);
		// command(cmd, envp);
	}
	pipefd[0] = new_pipe[0];
	pipefd[1] = new_pipe[1];
	return (0);
}

void afficher_contenu(char **tableau) {
    printf("tableau :\n");
    for (int i = 0; tableau[i] != NULL; ++i) {
        printf("%s\n", tableau[i]); // Affichage de chaque chaîne de caractères
    }
}

void	end_command(t_command cmd, char **envp)
{
	free(envp);
	free(cmd.args);
	if (cmd.outfile != -2 && cmd.outfile != 1)
		close(cmd.outfile);
}
void afficherContenuFichier(int fd) {
    char buffer[1024]; // Un tampon de 1024 octets pour stocker les données lues du fichier

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

int	find_file(t_command *cmd, t_token *line)
{
	if ((*line) && (*line)->type == 3)
	{
		cmd->infile = open((*line)->str, O_RDONLY, 0644);
		(*line) = (*line)->next;
	}
	else if ((*line) && (*line)->type == 4)
	{
		cmd->infile = get_here_doc((*line)->str);
		(*line) = (*line)->next;
	}
	if ((*line) && (*line)->type == 5)
	{
		cmd->outfile = open((*line)->str,  O_WRONLY | O_CREAT | O_TRUNC, 420);
		(*line) = (*line)->next;
	}
	else if ((*line) && (*line)->type == 6)
	{
		cmd->outfile = open((*line)->str,  O_WRONLY | O_CREAT | O_APPEND, 420);
		(*line) = (*line)->next;
	}
	if (cmd->outfile == -1 || cmd->infile == -1)
		return (1);
	else
		return (0);
}

void	start_command(t_minishell mini, int pipefd[2])
{	
	t_command	command;
	char	**envp;

	envp = tenv_to_arr(mini->env);
	if (!envp)
		return ;
	if (mini->cmd_line->type == 0)
		return (builtin(mini, pipefd, envp), 0);
	command.cmd = mini->cmd_line->str;
	command.infile = -2;
	command.outfile = -2;
	command.args = take_args(&mini->cmd_line);
	if (find_file(&command,  &mini->cmd_line) == 1)
		return (1); // fermer fd et free
	if (mini->cmd_line == NULL && command.outfile == -2)
		command.outfile = 1;
	else if (mini->cmd_line && mini->cmd_line->type == 7)
		mini->cmd_line = mini->cmd_line->next;
	commande(command, pipefd, envp);
	end_command(command, envp);
	return (0);
}

void	start_exe(t_minishell mini)
{
	int	pipefd[2];
	pid_t	pid;

	(void)mini;
	if (pipe(pipefd) == -1)
		ft_error("Pipe");
	pid	= fork();
	if (pid < 0)
		ft_error("Fork");
	else if (pid == 0)
	{
		while (mini->cmd_line != NULL)
			start_command(mini, pipefd);
	}
	wait(&pid);
}
