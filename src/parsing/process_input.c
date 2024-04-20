/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:38:53 by jules             #+#    #+#             */
/*   Updated: 2024/04/20 19:24:55 by jbanacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	new_token(char *str)
{
	t_token	tok;

	if (!str)
		return (NULL);
	tok = malloc(sizeof(struct s_token));
	if (!tok)
		return (NULL);
	tok->next = NULL;
	tok->prev = NULL;
	tok->str = str;
	return (tok);
}

void free_token(t_token tok)
{
	if (!tok)
		return ;
	free(tok->str);
	free(tok);
}

t_token	token_from_arr(char **arr, t_token prev)
{
	t_token	tok;

	if (!arr || !(arr[0]))
		return (NULL);
	tok = malloc(sizeof(struct s_token));
	if (!tok)
		return (NULL);
	tok->prev = prev;
	tok->str = arr[0];
	tok->next = token_from_arr(arr + 1, tok);
	if (!(tok->next) && arr[1])
	{
		free_token(tok);
		return (NULL);
	}
	return (tok);
}

void	put_token_type(t_token tok)
{
	if (!tok)
		return ;
	tok->type = ARG;
	if (!tok->prev || tok->prev->type == PIPE)
		tok->type = CMD;
	if (tok->str[0] == '|')
		tok->type = PIPE;
	if (strncmp(">>", tok->str))
		tok->type = OUTFILE_APPEND;
	if (strncmp(">", tok->str))
		tok->type = OUTFILE;
	if (strncmp("<", tok->str))
		tok->type = INFILE;
	if (strncmp("<<", tok->str))
		tok->type = INFILE_HEREDOC;
	
}

t_token	tokenize_input(char *line)
{
	char	**splitted_input;
	t_token	toknized_line;

	splitted_input = ft_split(line, ' ');
	if (!splitted_input)
		return (NULL);
	toknized_line = token_from_arr(splitted_input);
	free(splitted_input);
	return (token_from_arr);
}
