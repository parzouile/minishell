/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:38:53 by jules             #+#    #+#             */
/*   Updated: 2024/04/15 12:35:03 by jbanacze         ###   ########.fr       */
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

t_token	tokenize_input(char *line)
{
	char	**splitted_input;
	t_token	toknized_line;

	splitted_input = ft_split(line, ' ');
	if (!splitted_input)
		return (NULL);
	toknized_line = token_from_arr(splitted_input);
}
