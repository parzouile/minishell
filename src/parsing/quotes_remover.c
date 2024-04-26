/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_remover.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:08:31 by jules             #+#    #+#             */
/*   Updated: 2024/04/26 23:58:14 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	str_remove_quotes(char *str)
{
	int		in_quotes;
	char	q_char;
	int		i;
	int		nb_quotes;

	i = -1;
	in_quotes = 0;
	nb_quotes = 0;
	while (str[++i])
	{
		if (((str[i] == '\'') || (str[i] == '\"')) && !in_quotes)
		{
			in_quotes = 1;
			q_char = str[i];
			nb_quotes++;
		}
		else if (((str[i] == '\'') || (str[i] == '\"')) && (str[i] == q_char))
		{
			in_quotes = 0;
			nb_quotes++;
		}
		else
			str[i - nb_quotes] = str[i];
	}
	str[i - nb_quotes] = 0;
}

int	remove_tokens_quotes(t_token tok)
{
	char	*n_str;

	if (!tok)
		return (0);
	str_remove_quotes(tok->str);
	n_str = ft_strdup(tok->str);
	if (!n_str)
		return (1);
	free(tok->str);
	tok->str = n_str;
	return (remove_tokens_quotes(tok->next));	
}