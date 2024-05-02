/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:42:43 by jbanacze          #+#    #+#             */
/*   Updated: 2024/05/02 12:33:55 by jbanacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_next(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	return (i);
}

int	add_next_node_hd(t_minishell mini, t_list **lst, char *str, int *in_dquotes)
{
	int		next;
	int		len_var;
	t_list	*new_node;
	char	*new_str;

	next = find_next(str, '$');
	len_var = 0;
	if (next)
		new_str = ft_substr(str, 0, next);
	else
	{
		len_var = value_length(str, *in_dquotes);
		new_str = get_expanded_value(mini, str, len_var);
	}
	if (!new_str)
		return (-1);
	new_node = ft_lstnew(new_str);
	if (!new_node)
		return (free(new_str), -1);
	ft_lstadd_back(lst, new_node);
	return (next + (len_var > 0) * len_var + 1 * (next == 0) * (len_var <= 0));
}

char	*expand_heredoc(t_minishell mini, char *str)
{
	t_list	*expanded_lst;
	char	*expanded_str;
	int		in_dquotes;
	int		i;
	int		step;

	expanded_lst = NULL;
	in_dquotes = 0;
	i = 0;
	while (str[i])
	{
		step = add_next_node_hd(mini, &expanded_lst, str + i, &in_dquotes);
		if (step == -1)
			return (ft_lstclear(&expanded_lst, free), NULL);
		i += step;
	}
	expanded_str = lst_to_str(expanded_lst);
	ft_lstclear(&expanded_lst, free);
	treat_quote_expanded(expanded_str, 1);
	return (expanded_str);
}
