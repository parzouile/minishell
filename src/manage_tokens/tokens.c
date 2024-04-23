/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:23:23 by jules             #+#    #+#             */
/*   Updated: 2024/04/23 19:23:49 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_type(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (PIPE);
	if (!ft_strcmp(str, "<"))
		return (INFILE);
	if (!ft_strcmp(str, "<<"))
		return (INFILE_HEREDOC);
	if (!ft_strcmp(str, ">"))
		return (OUTFILE);
	if (!ft_strcmp(str, ">>"))
		return (OUTFILE_APPEND);
	return (ARG);
}

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
	tok->type = get_type(str);
	return (tok);
}

void	free_token(t_token tok)
{
	if (!tok)
		return ;
	free(tok->str);
	free(tok);
}

void	free_tokens(t_token tok)
{
	if (!tok)
		return ;
	free_tokens(tok->next);
	free_token(tok);
}

int	push_back(t_token *tok, t_token new)
{
	int	return_value;

	if (!tok || !new)
		return (1);
	if (!(*tok))
	{
		*tok = new;
		return (0);
	}
	return_value = push_back(&((*tok)->next), new);
	if ((*tok)->next)
		(*tok)->next->prev = *tok;
	return (return_value);
}
