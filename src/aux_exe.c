/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 09:41:21 by aschmitt          #+#    #+#             */
/*   Updated: 2024/05/02 13:21:49 by jbanacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nb_args(t_token line)
{
	int	i;

	i = 0;
	while ((line->type == 2 || line->type == 1))
	{
		i++;
		if (line->next == NULL)
			break ;
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
		return (perror("minishell"), NULL);
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
	free(cmd.args);
	if (cmd.outfile >= 0 && cmd.outfile != 1)
		close(cmd.outfile);
	if (cmd.infile >= 0)
		close(cmd.infile);
}

void	open_file(t_command *cmd, t_token *line, t_minishell mini)
{
	if ((*line) && (*line)->type == 3)
	{
		if (cmd->infile != -2)
			close(cmd->infile);
		cmd->infile = open((*line)->str, O_RDONLY, 0644);
	}
	else if ((*line) && ((*line)->type == 4 || (*line)->type == 8))
	{
		if (cmd->infile != -2)
			close(cmd->infile);
		
		cmd->infile = get_here_doc((*line)->str, mini, cmd);
	}
	else if ((*line) && (*line)->type == 5)
	{
		if (cmd->outfile != -2)
			close(cmd->outfile);
		cmd->outfile = open((*line)->str, O_WRONLY | O_CREAT | O_TRUNC, 420);
	}
	else if ((*line) && (*line)->type == 6)
	{
		if (cmd->outfile != -2)
			close(cmd->outfile);
		cmd->outfile = open((*line)->str, O_WRONLY | O_CREAT | O_APPEND, 420);
	}
}

int	redirection(t_command *cmd, t_token *line, t_minishell mini)
{
	cmd->infile = -2;
	cmd->outfile = -2;
	while ((*line) && ((*line)->type == 3 || (*line)->type == 4
			|| (*line)->type == 5 || (*line)->type == 6 || (*line)->type == 8))
	{
		open_file(cmd, line, mini);
		if (cmd->infile == -1)
		{
			if (cmd->outfile != -2)
				close(cmd->outfile);
			g_current_status = 1, error_msg("minishell: ");
			return (perror((*line)->str), 0);
		}
		if (cmd->outfile == -1)
		{
			if (cmd->infile != -2)
				close(cmd->infile);
			g_current_status = 1, error_msg("minishell: ");
			return (perror((*line)->str), 0);
		}
		if (!(*line)->next || cmd->exec == 1)
			break ;
		(*line) = (*line)->next;
	}
	return (1);
}
