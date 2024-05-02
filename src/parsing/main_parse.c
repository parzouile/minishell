/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 23:41:16 by jules             #+#    #+#             */
/*   Updated: 2024/05/02 13:05:46 by jbanacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verif_quotes(char *str)
{
	int		i;
	int		in_quotes;
	char	q_char;

	i = 0;
	in_quotes = 0;
	while (str[i])
	{
		if (((str[i] == '\'') || (str[i] == '\"')) && !in_quotes)
		{
			in_quotes = 1;
			q_char = str[i];
		}
		else if (((str[i] == '\'') || (str[i] == '\"')) && (str[i] == q_char))
			in_quotes = 0;
		i++;
	}
	return (in_quotes);
}

int	is_redirection(int type)
{
	if (type == INFILE)
		return (1);
	if (type == INFILE_HEREDOC)
		return (1);
	if (type == OUTFILE)
		return (1);
	if (type == OUTFILE_APPEND)
		return (1);
	if (type == INFILE_HEREDOC_NO_EXPAND)
		return (1);
	return (0);
}

//check for 2 pipes and 2 redirections next to eachothers
int	verif_syntaxe(t_token tok)
{
	if (!tok)
		return (0);
	if (tok->type == PIPE)
	{
		if (!(tok->prev) || !(tok->next))
			return (error_msg("Missing features around pipe\n"));
		if (tok->next->type == PIPE)
			return (error_msg("Two consecutive pipes\n"));
	}
	if (is_redirection(tok->type))
	{
		if (!(tok->next) || (tok->next->type == PIPE))
			return (error_msg("Missing redirection file\n"));
		if (is_redirection(tok->next->type))
			return (error_msg("Two consecutive redirections\n"));
	}
	return (verif_syntaxe(tok->next));
}

//Check " " && ' '
//expand
//tokenize
//rem " " && ' '
//check syntaxe
// put cmd types
//
int	parse(t_minishell mini, char *str)
{
	char	*expanded_str;

	if (verif_quotes(str))
		return (error_msg("Unmatched quotes\n"));
	expanded_str = expand_str(mini, str);
	if (!expanded_str)
		return (error_msg("Error during expansion\n"));
	if (tokenize(&(mini->cmd_line), expanded_str))
		return (free(expanded_str), error_msg("Error during tokenization\n"));
	free(expanded_str);
	if (verif_syntaxe(mini->cmd_line))
		return (error_msg("Syntaxe Error\n"));
	mini->cmd_line = contract_and_move_redirections(mini->cmd_line);
	if (remove_tokens_quotes(mini->cmd_line))
		return (error_msg("Error during the removal of quotes\n"));
	put_cmd_types(mini->cmd_line);
	return (0);
}
