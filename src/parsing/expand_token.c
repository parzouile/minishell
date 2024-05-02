/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:00:38 by jbanacze          #+#    #+#             */
/*   Updated: 2024/05/02 12:33:16 by jbanacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	value_length(char *str, int in_dquotes)
{
	int	i;

	if (!str[1] || (str[1] == ' '))
		return (0);
	if (ft_isdigit(str[1]) || str[1] == '?')
		return (2);
	if (!is_valid_char(str[1]))
		return (in_dquotes - 1);
	i = 1;
	while (str[i] && is_valid_char(str[i]))
		i++;
	return (i);
}

char	*handle_question_mark(void)
{
	return (ft_itoa(g_current_status));
}

char	*get_expanded_value(t_minishell mini, char *str, int len_var)
{
	char	*var_name;
	char	*value;

	if (len_var == -1)
		return (ft_calloc(1, sizeof(char)));
	if (len_var == 0)
	{
		value = ft_calloc(2, sizeof(char));
		if (!value)
			return (NULL);
		value[0] = '$';
		return (value);
	}
	if (str[1] == '?')
		return (handle_question_mark());
	var_name = ft_substr(str, 1, len_var - 1);
	value = get_value(mini->env, var_name);
	if (var_name)
		free(var_name);
	if (!value)
		return (NULL);
	treat_quote_expanded(value, 0);
	return (value);
}

int	add_next_node(t_minishell mini, t_list **lst, char *str, int *in_dquotes)
{
	int		next;
	int		len_var;
	t_list	*new_node;
	char	*new_str;

	next = next_dollar_sign(str, in_dquotes);
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

char	*expand_str(t_minishell mini, char *str)
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
		step = add_next_node(mini, &expanded_lst, str + i, &in_dquotes);
		if (step == -1)
			return (ft_lstclear(&expanded_lst, free), NULL);
		i += step;
	}
	expanded_str = lst_to_str(expanded_lst);
	ft_lstclear(&expanded_lst, free);
	return (expanded_str);
}
