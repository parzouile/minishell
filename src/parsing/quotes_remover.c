/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_remover.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:08:31 by jules             #+#    #+#             */
/*   Updated: 2024/05/02 13:05:22 by jbanacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_quotes(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] == '"') || (s[i] == '\''))
			return (1);
		i++;
	}
	return (0);
}

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
	if (has_quotes(tok->str) && (tok->type == INFILE_HEREDOC))
		tok->type = INFILE_HEREDOC_NO_EXPAND;
	str_remove_quotes(tok->str);
	n_str = ft_strdup(tok->str);
	if (!n_str)
		return (1);
	free(tok->str);
	tok->str = n_str;
	treat_quote_expanded(tok->str, 1);
	return (remove_tokens_quotes(tok->next));
}
