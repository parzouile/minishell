/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:40:51 by jules             #+#    #+#             */
/*   Updated: 2024/04/10 04:22:32 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef enum e_type
{
	cmd,
	arg
}	t_type;

typedef struct s_token	*t_token;
typedef struct s_env	*t_env;

struct s_token
{
	char	*str;
	int		type;
	t_token	prev;
	t_token	next;
};

struct s_env
{
	char	*value;
	t_env	next;
};

typedef struct s_minishell
{
	t_token	cmd_line;
	t_env	env;
}	*t_minishell;

#endif