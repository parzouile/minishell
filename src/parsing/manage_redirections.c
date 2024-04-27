/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:52:08 by jbanacze          #+#    #+#             */
/*   Updated: 2024/04/27 15:52:25 by jbanacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	contract_redirections(t_token tok)
{
	t_token	n_next;

	if (!tok)
		return ;
	if (is_redirection(tok->type))
	{
		free(tok->str);
		tok->str = tok->next->str;
		tok->next->str = NULL;
		n_next = tok->next->next;
		free_token(tok->next);
		tok->next = n_next;
		if (n_next)
			tok->next->prev = tok;
	}
	contract_redirections(tok->next);
}

t_token	swap_with_next(t_token tok)
{
	t_token	n_tok;

	if (!tok)
		return (NULL);
	if (!(tok->next))
		return (tok);
	n_tok = tok->next;
	tok->next = n_tok->next;
	if (tok->next)
		tok->next->prev = tok;
	n_tok->prev = tok->prev;
	if (tok->prev)
		tok->prev->next = n_tok;
	tok->prev = n_tok;
	n_tok->next = tok;
	return (n_tok);
}

int	move_one_step(t_token *tok)
{
	int		moved;
	t_token	next;

	printf("STEP--------------\n\n");
	print_token(*tok);
	if (!tok || !(*tok))
		return (0);
	moved = 0;
	next = (*tok)->next;
	if (is_redirection((*tok)->type))
	{
		if (next && ((next->type == ARG) || (next->type == CMD)))
		{
			moved = 1;
			*tok = swap_with_next(*tok);
		}
	}
	return (move_one_step(&((*tok)->next)) || moved);
}

t_token	contract_and_move_redirections(t_token tok)
{
	contract_redirections(tok);
	while (move_one_step(&tok))
		;
	return (tok);
}
